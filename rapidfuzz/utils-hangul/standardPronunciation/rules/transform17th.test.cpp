#include "transform17th.hpp"
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

TEST_CASE("transform17th", "[transform17th]")
{
    SECTION("받침 \"ㄷ\", \"ㅌ(ㄾ)\"이 조사나 접미사의 모음 \"ㅣ\"와 결합되는 경우에는, \"ㅈ\", \"ㅊ\"으로 "
            "바꾸어서 뒤 음절 첫소리로 옮겨 발음한다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"굳"));
        const auto& next = defined(disassembleCompleteCharacter(L"이"));

        const auto& result = transform17th(current, next);

        REQUIRE(result.current.choseong == L"ㄱ");
        REQUIRE(result.current.jungseong == L"ㅜ");
        REQUIRE(result.current.jongseong == L"");

        REQUIRE(result.next.choseong == L"ㅈ");
        REQUIRE(result.next.jungseong == L"ㅣ");
        REQUIRE(result.next.jongseong == L"");
    }

    SECTION("\"ㄷ\" 뒤에 접미사 \"히\"가 결합되어 \"티\"를 이루는 것은 \"치\"로 발음한다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"굳"));
        const auto& next = defined(disassembleCompleteCharacter(L"히"));

        const auto& result = transform17th(current, next);

        REQUIRE(result.current.choseong == L"ㄱ");
        REQUIRE(result.current.jungseong == L"ㅜ");
        REQUIRE(result.current.jongseong == L"");

        REQUIRE(result.next.choseong == L"ㅊ");
        REQUIRE(result.next.jungseong == L"ㅣ");
        REQUIRE(result.next.jongseong == L"");
    }
}
} // namespace Rules
} // namespace StandardPronunciation
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz