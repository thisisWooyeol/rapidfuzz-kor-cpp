#include "numberToHangul.hpp"
#include <algorithm>
#include <vector>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace NumberToHangul {

/**
 * @brief Converts a numerical value to its corresponding Hangul (Korean) representation.
 */
std::wstring numberToHangul(long long input, bool spacing)
{
    if (input < 0) {
        throw std::out_of_range("음수는 지원되지 않습니다.");
    }

    if (input == 0) {
        return L"영";
    }

    std::vector<std::wstring> koreanParts;
    std::wstring remainingDigits = std::to_wstring(input);
    int placeIndex = 0;

    // 4 자리씩 끊어서 변환, e.g. 123456789 -> [6789, 2345, 1]
    // 이후 역방향 순회를 통해 1, 2345, 6789 순으로 변환
    while (!remainingDigits.empty()) {
        std::wstring currentPart = L"";
        if (remainingDigits.length() > 4) {
            currentPart = remainingDigits.substr(remainingDigits.length() - 4, 4);
            remainingDigits = remainingDigits.substr(0, remainingDigits.length() - 4);
        }
        else {
            currentPart = remainingDigits;
            remainingDigits = L"";
        }

        int partNumber = std::stoi(currentPart);
        if (partNumber > 0) {
            std::wstring hangulPart = numberToKoreanUpToThousand(partNumber);
            hangulPart += _Internal::HANGUL_DIGITS[placeIndex];
            koreanParts.emplace_back(hangulPart);
        }

        placeIndex++;
    }

    std::wstring result = L"";
    for (auto it = koreanParts.rbegin(); it != koreanParts.rend(); ++it) {
        if (*it != L"") { // Skip empty parts
            result += *it;
        }
        if (spacing && it != koreanParts.rend() - 1) {
            result += L" ";
        }
    }
    return result;
}

/**
 * @brief Helper function to convert a number up to 9999 into its Hangul representation.
 */
std::wstring numberToKoreanUpToThousand(int num)
{
    if (num < 0 || num > 9999) {
        throw std::invalid_argument("0 이상 9999 이하의 숫자만 입력 가능합니다.");
    }

    if (num == 0) {
        return L"";
    }

    std::wstring koreanDigits;
    int digits[] = {1000, 100, 10, 1};
    int index = 0;

    for (int divisor : digits) {
        int quotient = num / divisor;
        num %= divisor;

        if (quotient == 0) {
            index++;
            continue;
        }

        // Skip '일' for thousand, hundred, and ten places
        if (quotient == 1 && (divisor == 1000 || divisor == 100 || divisor == 10)) {
            koreanDigits += _Internal::HANGUL_CARDINAL[index];
        }
        else {
            koreanDigits += _Internal::HANGUL_NUMBERS[quotient] + _Internal::HANGUL_CARDINAL[index];
        }

        index++;
    }

    return koreanDigits;
}

} // namespace NumberToHangul
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz
