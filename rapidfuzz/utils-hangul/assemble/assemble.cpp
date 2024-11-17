#include "assemble.hpp"

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace Assemble {

std::wstring assemble(const std::vector<std::wstring>& words)
{
    // Join the input words into a single string
    std::wstring joinedWords;
    for (const auto& word : words) {
        joinedWords += word;
    }

    // Disassemble the joined string into individual characters
    std::wstring disassembled = Disassemble::disassemble(joinedWords);

    // Handle empty disassembled string
    if (disassembled.empty()) {
        return L"";
    }

    // Initialize the assembled string with the first character
    std::wstring assembled(1, disassembled[0]);

    // Reduce the vector of characters using binaryAssemble to form the final assembled string
    for (size_t i = 1; i < disassembled.size(); ++i) {
        assembled = _Internal::binaryAssemble(assembled, std::wstring(1, disassembled[i]));
    }

    return assembled;
}

} // namespace Assemble
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz
