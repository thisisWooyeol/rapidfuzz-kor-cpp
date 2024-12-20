#include "hangulPreprocessor.hpp"

#include "assemble/assemble.hpp"
#include "convertQwertyToAlphabet/convertQwertyToAlphabet.hpp"
#include "disassemble/disassemble.hpp"
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
        case PreprocessOption::ReassembleHangul: std::cout << "  오타 재조합\n"; break;
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
 * 2. ReassembleHangul
 * 3. ApplyStandardPronunciation
 * 4. ExtractChoseong
 * 5. RomanizeHangul
 */
HangulType HangulPreprocessor::preprocess(const HangulType& input)
{
    HangulType result = input;
    if (log_level_ == LogLevel::Debug) {
        std::cout << "\n[DEBUG] 입력: " << wstring_to_utf8(result) << "\n";
    }

    for (const auto& option : settings_) {
        switch (option) {
        case PreprocessOption::ConvertQwertyToHangul: result = convertQwertyToHangul(result); break;
        case PreprocessOption::ReassembleHangul: result = reassembleHangul(result); break;
        case PreprocessOption::ApplyStandardPronunciation: result = applyStandardPronunciation(result); break;
        case PreprocessOption::ExtractChoseong: result = extractChoseong(result); break;
        case PreprocessOption::RomanizeHangul: result = romanizeHangul(result); break;
        }

        if (log_level_ == LogLevel::Debug) {
            std::cout << "[DEBUG] 전처리 옵션: ";
            switch (option) {
            case PreprocessOption::ConvertQwertyToHangul: std::cout << "QWERTY -> 한글 변환\n"; break;
            case PreprocessOption::ReassembleHangul: std::cout << "오타 재조합\n"; break;
            case PreprocessOption::ApplyStandardPronunciation: std::cout << "표준 발음 적용\n"; break;
            case PreprocessOption::ExtractChoseong: std::cout << "초성 추출\n"; break;
            case PreprocessOption::RomanizeHangul: std::cout << "로마자 변환\n"; break;
            }
            std::cout << "[DEBUG] 결과: " << wstring_to_utf8(result) << "\n";
        }
    }

    return result;
}

HangulType HangulPreprocessor::convertQwertyToHangul(const HangulType& input)
{
    return RapidFuzz::Utils::Hangul::ConvertQwertyToAlphabet::convertQwertyToHangul(input);
}

HangulType HangulPreprocessor::reassembleHangul(const HangulType& input)
{
    HangulType result = RapidFuzz::Utils::Hangul::Disassemble::disassemble(input);

    std::vector<HangulType> characters;
    for (const auto& ch : result) {
        characters.push_back(HangulType(1, ch));
    }
    return RapidFuzz::Utils::Hangul::Assemble::assemble(characters);
}

HangulType HangulPreprocessor::applyStandardPronunciation(const HangulType& input)
{
    return RapidFuzz::Utils::Hangul::StandardPronunciation::standardizePronunciation(input);
}

HangulType HangulPreprocessor::extractChoseong(const HangulType& input)
{
    return RapidFuzz::Utils::Hangul::GetChoseong::getChoseong(input);
}

HangulType HangulPreprocessor::romanizeHangul(const HangulType& input)
{
    return RapidFuzz::Utils::Hangul::Romanize::romanize(input);
}