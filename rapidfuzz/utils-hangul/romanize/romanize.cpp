#include "romanize.hpp"
#include "_internal/hangul.hpp"
#include "_internal/utils.hpp"
#include "assemble/assemble.hpp"
#include "canBe/canBe.hpp"
#include "constants.hpp"
#include "disassembleCompleteCharacter/disassembleCompleteCharacter.hpp"
#include "standardPronunciation/standardPronunciation.hpp"

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace Romanize {

std::wstring romanizeSyllableHangul(const std::vector<std::wstring>& arrayHangul, size_t index)
{
    std::wstring syllable = arrayHangul[index];

    // Check if the syllable is a Hangul character
    if (_Internal::isHangulCharacter(syllable)) {
        auto disassemble =
            DisassembleCompleteCharacter::disassembleCompleteCharacter(std::wstring(1, syllable[0]));
        if (!disassemble.has_value()) {
            // If disassembly fails, return the syllable as is
            return syllable;
        }

        // Extract components
        std::wstring choseong = disassemble.value().choseong;
        std::wstring jungseong = Assemble::assemble(std::vector{disassemble.value().jungseong});
        std::wstring jongseong = disassemble.value().jongseong;

        // Map components to Roman letters
        std::wstring romanChoseong = L"";
        std::wstring romanJungseong = L"";
        std::wstring romanJongseong = L"";

        // Map Choseong
        auto itChoseong = 초성_알파벳_발음.find(choseong[0]);
        if (itChoseong != 초성_알파벳_발음.end()) {
            romanChoseong = itChoseong->second;
        }

        // Map Jungseong
        auto itJungseong = 중성_알파벳_발음.find(jungseong[0]);
        if (itJungseong != 중성_알파벳_발음.end()) {
            romanJungseong = itJungseong->second;
        }

        // Map Jongseong
        if (!jongseong.empty()) {
            auto itJongseong = 종성_알파벳_발음.find(jongseong);
            if (itJongseong != 종성_알파벳_발음.end()) {
                romanJongseong = itJongseong->second;
            }
        }

        // Special handling for 'ㄹ'
        if (choseong == L"ㄹ") {
            if (index > 0 && _Internal::isHangulCharacter(arrayHangul[index - 1])) {
                auto prevDisassemble = DisassembleCompleteCharacter::disassembleCompleteCharacter(
                    std::wstring(1, arrayHangul[index - 1][0]));
                if (prevDisassemble.has_value() && prevDisassemble->jongseong == L"ㄹ") {
                    romanChoseong = L"l";
                }
            }
        }

        // Assemble the Romanized syllable
        return romanChoseong + romanJungseong + romanJongseong;
    }

    // If syllable is a vowel
    auto itVowel = 중성_알파벳_발음.find(syllable[0]);
    if (itVowel != 중성_알파벳_발음.end()) {
        return itVowel->second;
    }

    // If syllable can be a Choseong
    if (CanBe::canBeChoseong(std::wstring(1, syllable[0]))) {
        auto itChoseong = 초성_알파벳_발음.find(syllable[0]);
        if (itChoseong != 초성_알파벳_발음.end()) {
            return itChoseong->second;
        }
    }

    // Return the syllable as is if no mapping is found
    return syllable;
}

std::wstring romanize(const std::wstring& hangul)
{
    StandardPronunciation::Options options = {false};
    std::wstring standardizedHangul = StandardPronunciation::standardizePronunciation(hangul, options);

    std::wstring romanized = L"";
    std::vector<std::wstring> arrayHangul{};
    for (size_t i = 0; i < standardizedHangul.length(); ++i) {
        arrayHangul.push_back(std::wstring(1, standardizedHangul[i]));
    }

    for (size_t i = 0; i < arrayHangul.size(); ++i) {
        romanized += romanizeSyllableHangul(arrayHangul, i);
    }

    return romanized;
}

} // namespace Romanize
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz
