#include "numberToHangulMixed.hpp"
#include <algorithm>
#include <iomanip>
#include <locale>
#include <sstream>
#include <vector>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace NumberToHangulMixed {

/**
 * @brief Helper function to format a number with thousand separators based on the current locale.
 *
 * @param num The number to format.
 * @return A std::wstring with thousand separators.
 *
 * @example
 * std::wstring formatted = formatWithThousandSeparators(12345); // "12,345"
 */
std::wstring formatWithThousandSeparators(long long num)
{
    std::wstring numStr = std::to_wstring(num);
    int pos = numStr.length() % 3;
    std::wstring formatted = numStr.substr(0, pos);

    for (int i = pos; i < numStr.length(); i += 3) {
        if (!formatted.empty()) {
            formatted += L",";
        }
        formatted += numStr.substr(i, 3);
    }

    return formatted;
}

/**
 * @brief Converts a numerical value to a mixed Hangul and numeric string representation.
 *
 * This function converts a number into its Hangul representation by splitting it into
 * 4-digit groups, converting each group to a localized string with thousand separators,
 * appending the corresponding Hangul digit (e.g., 만, 억), and assembling the parts.
 *
 * @param input The numerical value to convert.
 * @param spacing Optional parameter to specify whether to include spaces between Hangul parts.
 * @return A std::wstring representing the mixed Hangul and numeric equivalent of the input number.
 *
 * @example
 * std::wstring result = numberToHangulMixed(12345, true); // "1만 2345"
 */
std::wstring numberToHangulMixed(long long input, bool spacing)
{
    if (input == 0) {
        return L"0";
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
            std::wstring formattedNumber = formatWithThousandSeparators(partNumber);
            std::wstring hangulPart = formattedNumber + _Internal::HANGUL_DIGITS[placeIndex];
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

} // namespace NumberToHangulMixed
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz
