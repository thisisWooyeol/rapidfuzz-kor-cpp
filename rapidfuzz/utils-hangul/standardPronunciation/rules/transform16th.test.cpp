#include "transform16th.hpp"
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

TEST_CASE("transform16th", "[transform16th]")
{
    SECTION("한글 자모의 이름은 그 받침소리를 연음하되, \"ㄷ, ㅈ, ㅊ, ㅋ, ㅌ, ㅍ, ㅎ\"의 경우에는 특별히 "
            "다음과 같이 발음한다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"귿"));
        const auto& next = defined(disassembleCompleteCharacter(L"이"));
        const std::wstring phrase = L"디귿이";
        const int index = 1;

        const auto& result = transform16th({current, next, phrase, index});

        REQUIRE(result.current.choseong == L"ㄱ");
        REQUIRE(result.current.jungseong == L"ㅡ");
        REQUIRE(result.current.jongseong == L"");

        REQUIRE(result.next.choseong == L"ㅅ");
        REQUIRE(result.next.jungseong == L"ㅣ");
        REQUIRE(result.next.jongseong == L"");
    }

    SECTION("자모의 이름이 \"ㄱ, ㄴ, ㄹ, ㅁ, ㅂ, ㅅ, ㅇ\"일 경우")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"역"));
        const auto& next = defined(disassembleCompleteCharacter(L"이"));
        const std::wstring phrase = L"기역이";
        const int index = 1;

        const auto& result = transform16th({current, next, phrase, index});

        REQUIRE(result.current.choseong == L"ㅇ");
        REQUIRE(result.current.jungseong == L"ㅕ");
        REQUIRE(result.current.jongseong == L"");

        REQUIRE(result.next.choseong == L"ㄱ");
        REQUIRE(result.next.jungseong == L"ㅣ");
        REQUIRE(result.next.jongseong == L"");
    }
}
} // namespace Rules
} // namespace StandardPronunciation
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz