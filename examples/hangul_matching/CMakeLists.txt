cmake_minimum_required(VERSION 3.10)
project(hangul_matching)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set the path to the ICU library (Bad practice, but it's a quick way to get it working)
set(ICU_INCLUDE_DIRS "/opt/homebrew/opt/icu4c/include")
set(ICU_LIBRARIES
    "/opt/homebrew/opt/icu4c/lib/libicuuc.dylib"
    "/opt/homebrew/opt/icu4c/lib/libicui18n.dylib"
    "/opt/homebrew/opt/icu4c/lib/libicudata.dylib"
)

find_package(rapidfuzz REQUIRED)

# Include the utils-hangul library
add_subdirectory(${CMAKE_SOURCE_DIR}/../../rapidfuzz/utils-hangul utils-hangul)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/../../rapidfuzz/utils-hangul
)

# Add the executable
add_executable(hangul_matching 
    main.cpp 
    HangulPreprocessor.cpp
    HangulPreprocessor.hpp
)

# Link libraries
target_link_libraries(hangul_matching
    PRIVATE
    RapidFuzzUtilsHangul   # The target name defined in utils-hangul's CMakeLists.txt
    rapidfuzz::rapidfuzz
    ${ICU_LIBRARIES}
)

# Set include directories for the target
target_include_directories(hangul_matching PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/../../rapidfuzz/utils-hangul
)
