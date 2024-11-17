#include "transformNLAssimilation.hpp"
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

TEST_CASE("transformNLAssimilation", "[transformNLAssimilation]")
{
    SECTION(
        "받침이 \"ㄱ, ㄴ, ㄷ, ㅁ, ㅂ, ㅇ\"이고 다음 음절이 \"야, 여, 요, 유, 이, 얘, 예\"로 이어지는 경우")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"맨"));
        const auto& next = defined(disassembleCompleteCharacter(L"입"));

        const auto& result = transformNLAssimilation(current, next);

        REQUIRE(result.current.choseong == L"ㅁ");
        REQUIRE(result.current.jungseong == L"ㅐ");
        REQUIRE(result.current.jongseong == L"ㄴ");

        REQUIRE(result.next.choseong == L"ㄴ");
        REQUIRE(result.next.jungseong == L"ㅣ");
        REQUIRE(result.next.jongseong == L"ㅂ");
    }

    SECTION("받침이 \"ㄹ\"이고 다음 음절이 \"야, 여, 요, 유, 이, 얘, 예\"로 이어지는 경우")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"알"));
        const auto& next = defined(disassembleCompleteCharacter(L"약"));

        const auto& result = transformNLAssimilation(current, next);

        REQUIRE(result.current.choseong == L"ㅇ");
        REQUIRE(result.current.jungseong == L"ㅏ");
        REQUIRE(result.current.jongseong == L"ㄹ");

        REQUIRE(result.next.choseong == L"ㄹ");
        REQUIRE(result.next.jungseong == L"ㅑ");
        REQUIRE(result.next.jongseong == L"ㄱ");
    }

    SECTION("ㄴ/ㄹ이 되기 위한 조건이지만 현재 음절의 중성의 ∙(아래아)가 하나가 아닐 경우에는 덧나지 않고 "
            "연음규칙이 적용된다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"양"));
        const auto& next = defined(disassembleCompleteCharacter(L"이"));

        const auto& result = transformNLAssimilation(current, next);

        REQUIRE(result.current.choseong == L"ㅇ");
        REQUIRE(result.current.jungseong == L"ㅑ");
        REQUIRE(result.current.jongseong == L"ㅇ");

        REQUIRE(result.next.choseong == L"ㅇ");
        REQUIRE(result.next.jungseong == L"ㅣ");
        REQUIRE(result.next.jongseong == L"");
    }
}
} // namespace Rules
} // namespace StandardPronunciation
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz