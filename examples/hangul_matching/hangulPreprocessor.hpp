#ifndef HANGUL_PREPROCESSOR_HPP
#define HANGUL_PREPROCESSOR_HPP

#include <string>
#include <vector>

enum class PreprocessOption {
    ConvertQwertyToHangul,
    ReassembleHangul,
    ApplyStandardPronunciation,
    ExtractChoseong,
    RomanizeHangul
};

using PreprocessSettings = std::vector<PreprocessOption>;
using HangulType = std::wstring;

enum class LogLevel { Debug, Warning };

class HangulPreprocessor {

public:
    HangulPreprocessor() = default;
    HangulPreprocessor(const PreprocessOption& settings);
    HangulPreprocessor(const PreprocessSettings& settings);

    // 로그 레벨을 설정합니다.
    void setLogLevel(LogLevel level);

    // 전처리 옵션을 설정합니다.
    HangulPreprocessor& addOption(PreprocessOption option);
    void printSettings();

    // 입력 문자열을 전처리하여 변환된 문자열을 반환합니다.
    HangulType preprocess(const HangulType& input);

    // 개별 전처리 기능에 대한 메소드
    HangulType convertQwertyToHangul(const HangulType& input);
    HangulType reassembleHangul(const HangulType& input);
    HangulType applyStandardPronunciation(const HangulType& input);
    HangulType extractChoseong(const HangulType& input);
    HangulType romanizeHangul(const HangulType& input);

private:
    PreprocessSettings settings_;
    LogLevel log_level_ = LogLevel::Warning;
};

#endif // HANGUL_PREPROCESSOR_HPP
