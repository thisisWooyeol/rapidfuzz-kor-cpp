#include "hangulPreprocessor.hpp"

#include "convertQwertyToAlphabet/convertQwertyToAlphabet.hpp"
#include "getChoseong/getChoseong.hpp"
#include "numberToHangulMixed/numberToHangulMixed.hpp"
#include "romanize/romanize.hpp"
#include "standardPronunciation/standardPronunciation.hpp"

HangulPreprocessor::HangulPreprocessor(const PreprocessSettings& settings) : settings_(settings)
{}

std::wstring HangulPreprocessor::preprocess(const std::wstring& input)
{
    std::wstring result = input;

    if (settings_.convertQwertyToHangul) {
        result = convertQwertyToHangul(result);
    }

    if (settings_.applyStandardPronunciation) {
        result = applyStandardPronunciation(result);
    }

    if (settings_.extractChoseong) {
        result = extractChoseong(result);
    }

    if (settings_.romanizeHangul) {
        result = romanizeHangul(result);
    }

    return result;
}

std::wstring HangulPreprocessor::convertQwertyToHangul(const std::wstring& input)
{
    return RapidFuzz::Utils::Hangul::ConvertQwertyToAlphabet::convertQwertyToAlphabet(input);
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