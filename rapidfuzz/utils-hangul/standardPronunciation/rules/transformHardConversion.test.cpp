#include "transformHardConversion.hpp"
#include "_internal/utils.hpp"
#include "disassembleCompleteCharacter/disassembleCompleteCharacter.hpp"
#include <catch2/catch_test_macros.hpp>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace StandardPronunciation {
namespace Rules {

using namespace _Internal;
using namespace DisassembleCompleteCharacter;

TEST_CASE("transformHardConversion", "[transformHardConversion]")
{
    SECTION("23항 - 받침 \"ㄱ(ㄲ, ㅋ, ㄳ, ㄺ), ㄷ(ㅅ, ㅆ, ㅈ, ㅊ, ㅌ), ㅂ(ㅍ, ㄼ, ㄿ, ㅄ)\" 뒤에 연결되는 "
            "\"ㄱ, ㄷ, ㅂ, ㅅ, ㅈ\"은 된소리로 발음한다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"국"));
        const auto& next = defined(disassembleCompleteCharacter(L"밥"));

        const auto& result = transformHardConversion(current, next);

        REQUIRE(result.next.choseong == L"ㅃ");
        REQUIRE(result.next.jungseong == L"ㅏ");
        REQUIRE(result.next.jongseong == L"ㅂ");
    }

    SECTION("24항 - 어간 받침 \"ㄴ(ㄵ), ㅁ(ㄻ)\" 뒤에 결합되는 어미의 첫소리 \"ㄱ, ㄷ, ㅅ, ㅈ\"은 된소리로 "
            "발음한다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"신"));
        const auto& next = defined(disassembleCompleteCharacter(L"고"));

        const auto& result = transformHardConversion(current, next);

        REQUIRE(result.next.choseong == L"ㄲ");
        REQUIRE(result.next.jungseong == L"ㅗ");
        REQUIRE(result.next.jongseong == L"");
    }

    SECTION("25항 - 어간 받침 \"ㄼ, ㄾ\" 뒤에 결합되는 어미의 첫소리 \"ㄱ, ㄷ, ㅅ, ㅈ\"은 된소리로 발음한다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"넓"));
        const auto& next = defined(disassembleCompleteCharacter(L"게"));

        const auto& result = transformHardConversion(current, next);

        REQUIRE(result.next.choseong == L"ㄲ");
        REQUIRE(result.next.jungseong == L"ㅔ");
        REQUIRE(result.next.jongseong == L"");
    }
}
} // namespace Rules
} // namespace StandardPronunciation
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz