#include "transform9And10And11th.hpp"
#include "_internal/utils.hpp"
#include "disassembleCompleteCharacter/disassembleCompleteCharacter.hpp"
#include <catch2/catch_test_macros.hpp>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace StandardPronunciation {
namespace Rules {

TEST_CASE("transform9And10And11th", "[transform9And10And11th]")
{
    SECTION("9항 - 받침 \"ㄲ, ㅋ\" / \"ㅅ, ㅆ, ㅈ, ㅊ, ㅌ\" / \"ㅍ\"은 어말 또는 자음 앞에서 각각 대표음 "
            "\"ㄱ, ㄷ, ㅂ\"으로 발음한다.")
    {
        const auto& current =
            _Internal::defined(DisassembleCompleteCharacter::disassembleCompleteCharacter(L"닦"));
        const auto& next = DisassembleCompleteCharacter::disassembleCompleteCharacter(L"다");

        const auto& result = transform9And10And11th(current, next);
        REQUIRE(result.current.choseong == L"ㄷ");
        REQUIRE(result.current.jungseong == L"ㅏ");
        REQUIRE(result.current.jongseong == L"ㄱ");
    }

    SECTION("10항 - 겹받침 \"ㄳ\" / \"ㄵ\" / \"ㄼ, ㄽ, ㄾ\" / \"ㅄ\"은 어말 또는 자음 앞에서 각각 \"ㄱ, ㄴ, "
            "ㄹ, ㅂ\"으로 발음한다.")
    {
        const auto& current =
            _Internal::defined(DisassembleCompleteCharacter::disassembleCompleteCharacter(L"앉"));
        const auto& next = DisassembleCompleteCharacter::disassembleCompleteCharacter(L"다");

        const auto& result = transform9And10And11th(current, next);
        REQUIRE(result.current.choseong == L"ㅇ");
        REQUIRE(result.current.jungseong == L"ㅏ");
        REQUIRE(result.current.jongseong == L"ㄴ");
    }

    SECTION(
        "11항 - 겹받침 \"ㄺ\" / \"ㄻ\" / \"ㄿ\"은 어말 또는 자음 앞에서 각각 \"ㄱ, ㅁ, ㅂ\"으로 발음한다.")
    {
        const auto& current =
            _Internal::defined(DisassembleCompleteCharacter::disassembleCompleteCharacter(L"흙"));
        const auto& next = DisassembleCompleteCharacter::disassembleCompleteCharacter(L"과");

        const auto& result = transform9And10And11th(current, next);
        REQUIRE(result.current.choseong == L"ㅎ");
        REQUIRE(result.current.jungseong == L"ㅡ");
        REQUIRE(result.current.jongseong == L"ㄱ");
    }
}
} // namespace Rules
} // namespace StandardPronunciation
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz