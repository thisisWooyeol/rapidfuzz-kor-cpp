#include "hangulPreprocessor.hpp"
#include "rapidfuzz/fuzz.hpp"
#include "utils.hpp"
#include <iostream>
#include <set>
#include <sstream>
#include <string>

int main()
{
    // 프로그램 설명 출력
    std::cout << "========================================================================\n";
    std::cout << "한글 문자열 유사도 비교 프로그램\n\n";
    std::cout << "이 프로그램은 두 개의 한글 문자열을 입력받아, 선택한 전처리 옵션을 적용한 후, \n";
    std::cout << "RapidFuzz 라이브러리를 사용하여 두 문자열의 유사도를 계산합니다.\n";
    std::cout << "한글은 자음과 모음의 결합으로 이루어진 복잡한 구조를 가지고 있어, \n";
    std::cout << "일반적으로 근사적인 문자열을 계산하는 fuzzy matching 알고리즘을 사용할 때, \n";
    std::cout << "정확한 유사도 계산이 어려울 수 있습니다.\n";
    std::cout << "Reference: https://github.com/rapidfuzz/RapidFuzz/issues/7\n\n";
    std::cout << "이를 해결하기 위해 다양한 전처리 옵션을 제공하여 보다 정확한 비교를 가능하게 합니다.\n\n";
    std::cout << "사용 가능한 전처리 옵션:\n";
    std::cout << "1 - QWERTY -> 한글 변환: 영문 QWERTY 자판으로 입력된 한글을 실제 한글로 변환합니다.\n";
    std::cout << "2 - 표준 발음 적용: 한글의 표준 발음 규칙을 적용하여 발음상 동일한 문자열로 변환합니다.\n";
    std::cout << "3 - 초성 추출: 한글 문자열에서 초성만 추출하여 비교합니다.\n";
    std::cout << "4 - 로마자 변환: 한글 문자열을 로마자 표기법으로 변환하여 비교합니다.\n";
    std::cout << "\n원하는 전처리 옵션을 선택하여 유사도 비교의 정확도를 높일 수 있습니다.\n";
    std::cout
        << "프로그램 사용을 시작하려면, 전처리 옵션을 선택한 후 비교할 두 개의 문자열을 입력하세요.\n\n";
    std::cout << "========================================================================\n\n";

    // Initialize Empty HangulPreprocessor
    HangulPreprocessor preprocessor;

    // ! NOTE 다음 로그 레벨을 Warning으로 설정해 전처리 과정 추적을 생략할 수 있습니다.
    preprocessor.setLogLevel(LogLevel::Debug);

    // Get options
    char option_;
    std::set<PreprocessOption> options;
    while (true) {
        std::cout << "[Step 1] 사용할 전처리 옵션을 선택하세요. q를 입력해 설정을 종료합니다.:\n";
        std::cout << "1 - QWERTY -> 한글 변환\n";
        std::cout << "2 - 표준 발음 적용\n";
        std::cout << "3 - 초성 추출\n";
        std::cout << "4 - 로마자 변환\n";
        std::cout << "q - 설정 종료\n";

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

    std::cout << "\n[Step 2] 비교할 두 문자열을 입력하세요.\n";
    // 첫 번째 입력 문자열 받기
    std::cout << "첫 번째 문자열을 입력하세요: ";
    std::string input_line1;
    std::getline(std::cin, input_line1);

    // 두 번째 입력 문자열 받기
    std::cout << "두 번째 문자열을 입력하세요: ";
    std::string input_line2;
    std::getline(std::cin, input_line2);

    // 입력 문자열을 std::wstring으로 변환
    std::wstring winput_line1 = utf8_to_wstring(input_line1);
    std::wstring winput_line2 = utf8_to_wstring(input_line2);

    // 문자열 전처리
    std::wstring wprocessed1 = preprocessor.preprocess(winput_line1);
    std::wstring wprocessed2 = preprocessor.preprocess(winput_line2);

    // 전처리된 결과를 UTF-8 std::string으로 변환
    std::string processed1 = wstring_to_utf8(wprocessed1);
    std::string processed2 = wstring_to_utf8(wprocessed2);

    // 전처리 결과 출력
    std::cout << "전처리된 첫 번째 문자열: " << processed1 << std::endl;
    std::cout << "전처리된 두 번째 문자열: " << processed2 << std::endl;

    // RapidFuzz를 사용하여 유사도 계산
    double similarity = rapidfuzz::fuzz::ratio(wprocessed1, wprocessed2);

    std::cout << "유사도: " << similarity << std::endl;

    return 0;
}
