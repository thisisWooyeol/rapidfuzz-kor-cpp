#include "hangulPreprocessor.hpp"
#include <codecvt>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>

// Conversion functions
std::wstring utf8_to_wstring(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

std::string wstring_to_utf8(const std::wstring& wstr)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

int main()
{
    // Set the global locale to UTF-8
    std::locale::global(std::locale(""));

    // User selects preprocessing options
    PreprocessSettings settings;

    std::cout << "사용할 전처리 옵션을 선택하세요 (예: 1 3 4):\n";
    std::cout << "1. QWERTY -> 한글 변환\n";
    std::cout << "2. 표준 발음 적용\n";
    std::cout << "3. 초성 추출\n";
    std::cout << "4. 로마자 변환\n";
    std::cout << "옵션 번호를 입력하고, 각 번호는 공백으로 구분합니다: ";

    std::string options_line;
    std::getline(std::cin, options_line);

    // Parse options
    std::istringstream options_stream(options_line);
    int option;
    while (options_stream >> option) {
        switch (option) {
        case 1: settings.convertQwertyToHangul = true; break;
        case 2: settings.applyStandardPronunciation = true; break;
        case 3: settings.extractChoseong = true; break;
        case 4: settings.romanizeHangul = true; break;
        default: std::cout << "잘못된 옵션 번호: " << option << std::endl; break;
        }
    }

    // Get input string
    std::cout << "입력할 문자열을 입력하세요: ";
    std::string input_line;
    std::getline(std::cin, input_line);

    // Convert input to std::wstring
    std::wstring winput_line = utf8_to_wstring(input_line);

    HangulPreprocessor preprocessor(settings);
    std::wstring wprocessed = preprocessor.preprocess(winput_line);

    // Convert processed result back to UTF-8 std::string
    std::string processed = wstring_to_utf8(wprocessed);

    std::cout << "전처리 결과: " << processed << std::endl;

    return 0;
}
