#include "transform19th.hpp"
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

TEST_CASE("transform19th", "[transform19th]")
{
    SECTION("받침 \"ㅁ, ㅇ\" 뒤에 연결되는 \"ㄹ\"은 \"ㄴ\"으로 발음한다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"담"));
        const auto& next = defined(disassembleCompleteCharacter(L"력"));

        const auto& result = transform19th(current, next);

        REQUIRE(result.next.choseong == L"ㄴ");
        REQUIRE(result.next.jungseong == L"ㅕ");
        REQUIRE(result.next.jongseong == L"ㄱ");
    }

    SECTION("받침 \"ㄱ, ㅂ\" 뒤에 연결되는 \"ㄹ\"도 \"ㄴ\"으로 발음한다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"막"));
        const auto& next = defined(disassembleCompleteCharacter(L"론"));

        const auto& result = transform19th(current, next);

        REQUIRE(result.next.choseong == L"ㄴ");
        REQUIRE(result.next.jungseong == L"ㅗ");
        REQUIRE(result.next.jongseong == L"ㄴ");
    }
}
} // namespace Rules
} // namespace StandardPronunciation
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz