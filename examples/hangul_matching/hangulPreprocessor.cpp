#include "hangulPreprocessor.hpp"

#include "assemble/assemble.hpp"
#include "convertQwertyToAlphabet/convertQwertyToAlphabet.hpp"
#include "getChoseong/getChoseong.hpp"
#include "numberToHangulMixed/numberToHangulMixed.hpp"
#include "romanize/romanize.hpp"
#include "standardPronunciation/standardPronunciation.hpp"

#include "utils.hpp"

#include <iostream>

HangulPreprocessor::HangulPreprocessor(const PreprocessOption& settings) : settings_({settings})
{}

HangulPreprocessor::HangulPreprocessor(const PreprocessSettings& settings) : settings_(settings)
{}

void HangulPreprocessor::setLogLevel(LogLevel level)
{
    log_level_ = level;
}

HangulPreprocessor& HangulPreprocessor::addOption(PreprocessOption option)
{
    settings_.push_back(option);
    return *this;
}

void HangulPreprocessor::printSettings()
{
    std::cout << "설정된 전처리 옵션 순서:\n";
    for (const auto& option : settings_) {
        switch (option) {
        case PreprocessOption::ConvertQwertyToHangul: std::cout << "  QWERTY -> 한글 변환\n"; break;
        case PreprocessOption::ApplyStandardPronunciation: std::cout << "  표준 발음 적용\n"; break;
        case PreprocessOption::ExtractChoseong: std::cout << "  초성 추출\n"; break;
        case PreprocessOption::RomanizeHangul: std::cout << "  로마자 변환\n"; break;
        }
    }
}

/**
 * @brief 입력 문자열을 설정된 전처리 옵션에 따라 변환합니다.
 * @remark 효과적인 전처리를 위해 다음 전처리 옵션을 권장합니다:
 * 1. ConvertQwertyToHangul
 * 2. ApplyStandardPronunciation
 * 3. ExtractChoseong
 * 4. RomanizeHangul
 */
std::wstring HangulPreprocessor::preprocess(const std::wstring& input)
{
    std::wstring result = input;

    for (const auto& option : settings_) {
        switch (option) {
        case PreprocessOption::ConvertQwertyToHangul: result = convertQwertyToHangul(result); break;
        case PreprocessOption::ApplyStandardPronunciation: result = applyStandardPronunciation(result); break;
        case PreprocessOption::ExtractChoseong: result = extractChoseong(result); break;
        case PreprocessOption::RomanizeHangul: result = romanizeHangul(result); break;
        }

        if (log_level_ == LogLevel::Debug) {
            std::cout << "[DEBUG] 전처리 옵션: ";
            switch (option) {
            case PreprocessOption::ConvertQwertyToHangul: std::cout << "QWERTY -> 한글 변환\n"; break;
            case PreprocessOption::ApplyStandardPronunciation: std::cout << "표준 발음 적용\n"; break;
            case PreprocessOption::ExtractChoseong: std::cout << "초성 추출\n"; break;
            case PreprocessOption::RomanizeHangul: std::cout << "로마자 변환\n"; break;
            }
            std::cout << "[DEBUG] 결과: " << wstring_to_utf8(result) << "\n\n";
        }
    }

    return result;
}

std::wstring HangulPreprocessor::convertQwertyToHangul(const std::wstring& input)
{
    return RapidFuzz::Utils::Hangul::ConvertQwertyToAlphabet::convertQwertyToHangul(input);
}

std::wstring HangulPreprocessor::extractChoseong(const std::wstring& input)
{
    return RapidFuzz::Utils::Hangul::GetChoseong::getChoseong(input);
}

std::wstring HangulPreprocessor::applyStandardPronunciation(const std::wstring& input)
{
    return RapidFuzz::Utils::Hangul::StandardPronunciation::standardizePronunciation(input);
}

std::wstring HangulPreprocessor::romanizeHangul(const std::wstring& input)
{
    return RapidFuzz::Utils::Hangul::Romanize::romanize(input);
}