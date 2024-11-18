#include "hangulPreprocessor.hpp"
#include "utils.hpp"
#include <iostream>
#include <set>
#include <sstream>
#include <string>

int main()
{
    // Initialize Empty HangulPreprocessor
    HangulPreprocessor preprocessor;

    // ! NOTE 다음 로그 레벨을 Warning으로 설정해 전처리 과정 추적을 생략할 수 있습니다.
    preprocessor.setLogLevel(LogLevel::Debug);

    // Get options
    char option_;
    std::set<PreprocessOption> options;
    while (true) {
        std::cout << "사용할 전처리 옵션을 선택하세요. q를 입력해 설정을 종료합니다.:\n";
        std::cout << "1 - QWERTY -> 한글 변환\n";
        std::cout << "2 - 표준 발음 적용\n";
        std::cout << "3 - 초성 추출\n";
        std::cout << "4 - 로마자 변환\n";
        std::cout << "q - 설정 종료\n\n";

        std::string options_line;
        std::getline(std::cin, options_line);
        std::istringstream options_stream(options_line);
        options_stream >> option_;

        if (option_ == 'q') {
            break;
        }

        preprocessor.addOption(static_cast<PreprocessOption>(option_ - '1'));
    }
    preprocessor.printSettings();

    // Get input string
    std::cout << "입력할 문자열을 입력하세요: ";
    std::string input_line;
    std::getline(std::cin, input_line);

    // Convert input to std::wstring
    std::wstring winput_line = utf8_to_wstring(input_line);

    std::wstring wprocessed = preprocessor.preprocess(winput_line);

    // Convert processed result back to UTF-8 std::string
    std::string processed = wstring_to_utf8(wprocessed);

    std::cout << "전처리 결과: " << processed << std::endl;

    return 0;
}
