#include "transform13And14th.hpp"
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

TEST_CASE("transform13And14th", "[transform13And14th]")
{
    SECTION("13항을 적용합니다.")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"깎"));
        const auto& next = defined(disassembleCompleteCharacter(L"아"));

        const auto& result = transform13And14th(current, next);
        REQUIRE(result.current.choseong == L"ㄲ");
        REQUIRE(result.current.jungseong == L"ㅏ");
        REQUIRE(result.current.jongseong == L"");

        REQUIRE(result.next.choseong == L"ㄲ");
        REQUIRE(result.next.jungseong == L"ㅏ");
        REQUIRE(result.next.jongseong == L"");
    }

    SECTION("14항을 적용합니다.")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"닭"));
        const auto& next = defined(disassembleCompleteCharacter(L"을"));

        const auto& result = transform13And14th(current, next);
        REQUIRE(result.current.choseong == L"ㄷ");
        REQUIRE(result.current.jungseong == L"ㅏ");
        REQUIRE(result.current.jongseong == L"ㄹ");

        REQUIRE(result.next.choseong == L"ㄱ");
        REQUIRE(result.next.jungseong == L"ㅡ");
        REQUIRE(result.next.jongseong == L"ㄹ");
    }
}
} // namespace Rules
} // namespace StandardPronunciation
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz