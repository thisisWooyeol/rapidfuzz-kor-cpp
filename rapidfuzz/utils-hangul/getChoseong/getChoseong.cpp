#include "getChoseong.hpp"
#include "_internal/constants.hpp"
#include <unicode/normalizer2.h>
#include <unicode/unistr.h>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace GetChoseong {

/**
 * @brief Helper function to normalize a wide string to NFD (Normalization Form D).
 *
 * **Note**: C++ does not have built-in support for Unicode normalization.
 * This function requires an external library such as ICU or Boost.Locale.
 * For demonstration purposes, this function is a stub and returns the input string unchanged.
 *
 * @param input The input wide string to normalize.
 * @return A `std::wstring` normalized to NFD.
 *
 * @throws `std::invalid_argument` if normalization fails.
 */
std::wstring normalizeNFD(const std::wstring& input)
{
    UErrorCode errorCode = U_ZERO_ERROR;
    const icu::Normalizer2* normalizer = icu::Normalizer2::getNFDInstance(errorCode);

    if (U_FAILURE(errorCode)) {
        throw std::invalid_argument("Failed to get NFD normalizer");
    }

    // Convert std::wstring to ICU UnicodeString
    icu::UnicodeString uInput =
        icu::UnicodeString::fromUTF32(reinterpret_cast<const UChar32*>(input.c_str()), input.length());

    // Normalize to NFD
    icu::UnicodeString uOutput;
    normalizer->normalize(uInput, uOutput, errorCode);

    if (U_FAILURE(errorCode)) {
        throw std::invalid_argument("Normalization to NFD failed");
    }

    // Determine the number of UTF-32 code points
    int32_t utf32Length = uOutput.countChar32();

    // Allocate space in the output wstring
    std::wstring output;
    output.reserve(utf32Length);

    // Temporary buffer to hold the UTF-32 code points
    std::vector<UChar32> buffer(utf32Length);
    uOutput.toUTF32(buffer.data(), utf32Length, errorCode);

    if (U_FAILURE(errorCode)) {
        throw std::invalid_argument("Conversion from UnicodeString to std::wstring failed");
    }

    // Assign the code points to the wstring
    for (int32_t i = 0; i < utf32Length; ++i) {
        output.push_back(static_cast<wchar_t>(buffer[i]));
    }

    return output;
}

/**
 * @brief 단어에서 초성을 추출합니다. (예: `사과` -> `'ㅅㄱ'`)
 *
 * @param word 초성을 추출할 단어
 * @return A `std::wstring` containing the extracted Choseong characters.
 *
 * @example
 * std::wstring result = getChoseong(L"사과"); // "ㅅㄱ"
 * std::wstring result = getChoseong(L"띄어 쓰기"); // "ㄸㅇ ㅆㄱ"
 */
std::wstring getChoseong(const std::wstring& word)
{
    std::wstring normalized = normalizeNFD(word);

    // NFD ㄱ-ㅎ, NFC ㄱ-ㅎ 외 문자 삭제
    std::wstring filtered = std::regex_replace(normalized, EXTRACT_CHOSEONG_REGEX, L"");

    // NFD to NFC
    std::wstring result;
    result.reserve(filtered.size());

    for (wchar_t wc : filtered) {
        if (static_cast<int>(wc) >= static_cast<int>(JASO_HANGUL_NFD::START_CHOSEONG) &&
            static_cast<int>(wc) <= static_cast<int>(JASO_HANGUL_NFD::END_CHOSEONG))
        {
            // Calculate the index into the CHOSEONGS array
            // 0x1100 : 'ㄱ' (NFC Choseong)
            int index = static_cast<int>(wc) - 0x1100;

            // Replace with the corresponding NFC Choseong character
            if (index >= 0 && index < _Internal::CHOSEONGS.size()) {
                result += _Internal::CHOSEONGS[index];
            }
            else {
                result += wc;
            }
        }
        else {
            // Append the character as is (e.g., NFC Choseong characters or whitespace)
            result += wc;
        }
    }

    return result;
}

} // namespace GetChoseong
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz
