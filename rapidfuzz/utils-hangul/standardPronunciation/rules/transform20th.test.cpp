#include "transform20th.hpp"
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

TEST_CASE("transform20th", "[transform20th]")
{
    SECTION("\"ㄴ\"은 \"ㄹ\"의 앞이나 뒤에서 \"ㄹ\"로 발음한다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"난"));
        const auto& next = defined(disassembleCompleteCharacter(L"로"));

        const auto& result = transform20th(current, next);

        REQUIRE(result.current.choseong == L"ㄴ");
        REQUIRE(result.current.jungseong == L"ㅏ");
        REQUIRE(result.current.jongseong == L"ㄹ");

        REQUIRE(result.next.choseong == L"ㄹ");
        REQUIRE(result.next.jungseong == L"ㅗ");
        REQUIRE(result.next.jongseong == L"");
    }

    SECTION("첫소리 \"ㄴ\"이 \"ㅀ, ㄾ\" 뒤에 연결되는 경우에도 \"ㄹ\"로 발음한다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"닳"));
        const auto& next = defined(disassembleCompleteCharacter(L"는"));

        const auto& result = transform20th(current, next);

        REQUIRE(result.current.choseong == L"ㄷ");
        REQUIRE(result.current.jungseong == L"ㅏ");
        REQUIRE(result.current.jongseong == L"ㄹㅎ");

        REQUIRE(result.next.choseong == L"ㄹ");
        REQUIRE(result.next.jungseong == L"ㅡ");
        REQUIRE(result.next.jongseong == L"ㄴ");
    }
}
} // namespace Rules
} // namespace StandardPronunciation
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz