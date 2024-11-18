#ifndef HANGUL_PREPROCESSOR_HPP
#define HANGUL_PREPROCESSOR_HPP

#include <string>

enum class PreprocessOption {
    ConvertQwertyToHangul,
    ApplyStandardPronunciation,
    ExtractChoseong,
    RomanizeHangul
};

struct PreprocessSettings {
    bool convertQwertyToHangul = false;
    bool applyStandardPronunciation = false;
    bool extractChoseong = false;
    bool romanizeHangul = false;
};

class HangulPreprocessor {
public:
    HangulPreprocessor(const PreprocessSettings& settings);

    // 입력 문자열을 전처리하여 변환된 문자열을 반환합니다.
    std::wstring preprocess(const std::wstring& input);

    // 개별 전처리 기능에 대한 메소드
    std::wstring convertQwertyToHangul(const std::wstring& input);
    std::wstring extractChoseong(const std::wstring& input);
    std::wstring applyStandardPronunciation(const std::wstring& input);
    std::wstring romanizeHangul(const std::wstring& input);

private:
    PreprocessSettings settings_;
};

#endif // HANGUL_PREPROCESSOR_HPP
