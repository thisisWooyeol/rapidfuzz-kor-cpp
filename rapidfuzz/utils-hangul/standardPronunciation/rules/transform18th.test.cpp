#include "transform18th.hpp"
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

TEST_CASE("transform18th", "[transform18th]")
{
    SECTION("받침 \"ㄱ, ㄲ, ㅋ, ㄳ, ㄺ\"일 경우")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"먹"));
        const auto& next = defined(disassembleCompleteCharacter(L"는"));

        const auto& result = transform18th(current, next);

        REQUIRE(result.current.choseong == L"ㅁ");
        REQUIRE(result.current.jungseong == L"ㅓ");
        REQUIRE(result.current.jongseong == L"ㅇ");
    }

    SECTION("받침 \"ㄷ, ㅅ, ㅆ, ㅈ, ㅊ, ㅌ, ㅎ\"일 경우")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"닫"));
        const auto& next = defined(disassembleCompleteCharacter(L"는"));

        const auto& result = transform18th(current, next);

        REQUIRE(result.current.choseong == L"ㄷ");
        REQUIRE(result.current.jungseong == L"ㅏ");
        REQUIRE(result.current.jongseong == L"ㄴ");
    }

    SECTION("받침 \"ㅂ, ㅍ, ㄼ, ㄿ, ㅄ\"일 경우")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"잡"));
        const auto& next = defined(disassembleCompleteCharacter(L"는"));

        const auto& result = transform18th(current, next);

        REQUIRE(result.current.choseong == L"ㅈ");
        REQUIRE(result.current.jungseong == L"ㅏ");
        REQUIRE(result.current.jongseong == L"ㅁ");
    }
}
} // namespace Rules
} // namespace StandardPronunciation
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz