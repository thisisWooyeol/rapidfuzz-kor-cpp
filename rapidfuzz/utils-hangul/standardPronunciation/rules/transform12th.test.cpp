#include "transform12th.hpp"
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

TEST_CASE("transform12th", "[transform12th]")
{
    SECTION("\"ㅎ, ㄶ, ㅀ\" 뒤에 \"ㄱ, ㄷ, ㅈ\"이 결합되는 경우에는, 뒤 음절 첫소리와 합쳐서 \"ㅋ, ㅌ, "
            "ㅊ\"으로 발음한다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"놓"));
        const auto& next = disassembleCompleteCharacter(L"고");

        const auto& result = transform12th(current, next);
        REQUIRE(result.current.choseong == L"ㄴ");
        REQUIRE(result.current.jungseong == L"ㅗ");
        REQUIRE(result.current.jongseong == L"");

        REQUIRE(result.next.has_value()); // As output type is Nullable<Syllable>
        REQUIRE(result.next->choseong == L"ㅋ");
        REQUIRE(result.next->jungseong == L"ㅗ");
        REQUIRE(result.next->jongseong == L"");
    }

    SECTION("받침 \"ㄱ, ㄺ, ㄷ, ㅂ, ㄼ, ㅈ, ㄵ\"이 뒤 음절 첫소리 \"ㅎ\"과 결합되는 경우에도, 역시 두 음을 "
            "합쳐서 \"ㅋ, ㅌ, ㅍ, ㅊ\"으로 발음한다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"각"));
        const auto& next = disassembleCompleteCharacter(L"하");

        const auto& result = transform12th(current, next);
        REQUIRE(result.current.choseong == L"ㄱ");
        REQUIRE(result.current.jungseong == L"ㅏ");
        REQUIRE(result.current.jongseong == L"");

        REQUIRE(result.next.has_value()); // As output type is Nullable<Syllable>
        REQUIRE(result.next->choseong == L"ㅋ");
        REQUIRE(result.next->jungseong == L"ㅏ");
        REQUIRE(result.next->jongseong == L"");
    }

    SECTION("\"ㅎ, ㄶ, ㅀ\" 뒤에 \"ㅅ\"이 결합되는 경우에는, \"ㅅ\"을 \"ㅆ\"으로 발음한다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"닿"));
        const auto& next = disassembleCompleteCharacter(L"소");

        const auto& result = transform12th(current, next);
        REQUIRE(result.current.choseong == L"ㄷ");
        REQUIRE(result.current.jungseong == L"ㅏ");
        REQUIRE(result.current.jongseong == L"");

        REQUIRE(result.next.has_value()); // As output type is Nullable<Syllable>
        REQUIRE(result.next->choseong == L"ㅆ");
        REQUIRE(result.next->jungseong == L"ㅗ");
        REQUIRE(result.next->jongseong == L"");
    }

    SECTION("\"ㅎ\" 뒤에 \"ㄴ\"이 결합되는 경우에는 \"ㄴ\"으로 발음한다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"놓"));
        const auto& next = disassembleCompleteCharacter(L"는");

        const auto& result = transform12th(current, next);
        REQUIRE(result.current.choseong == L"ㄴ");
        REQUIRE(result.current.jungseong == L"ㅗ");
        REQUIRE(result.current.jongseong == L"");

        REQUIRE(result.next.has_value()); // As output type is Nullable<Syllable>
        REQUIRE(result.next->choseong == L"ㄴ");
        REQUIRE(result.next->jungseong == L"ㅡ");
        REQUIRE(result.next->jongseong == L"ㄴ");
    }

    SECTION("\"ㄶ, ㅀ\" 뒤에 \"ㄴ\"이 결합되는 경우에는, \"ㅎ\"을 발음하지 않는다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"않"));
        const auto& next = disassembleCompleteCharacter(L"네");

        const auto& result = transform12th(current, next);
        REQUIRE(result.current.choseong == L"ㅇ");
        REQUIRE(result.current.jungseong == L"ㅏ");
        REQUIRE(result.current.jongseong == L"ㄴ");

        REQUIRE(result.next.has_value()); // As output type is Nullable<Syllable>
        REQUIRE(result.next->choseong == L"ㄴ");
        REQUIRE(result.next->jungseong == L"ㅔ");
        REQUIRE(result.next->jongseong == L"");
    }

    SECTION("\"ㅎ, ㄶ, ㅀ\" 뒤에 모음으로 시작된 어미나 접미사가 결합되는 경우에는 \"ㅎ\"을 발음하지 않는다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"낳"));
        const auto& next = disassembleCompleteCharacter(L"은");

        const auto& result = transform12th(current, next);
        REQUIRE(result.current.choseong == L"ㄴ");
        REQUIRE(result.current.jungseong == L"ㅏ");
        REQUIRE(result.current.jongseong == L"");

        REQUIRE(result.next.has_value()); // As output type is Nullable<Syllable>
        REQUIRE(result.next->choseong == L"ㅇ");
        REQUIRE(result.next->jungseong == L"ㅡ");
        REQUIRE(result.next->jongseong == L"ㄴ");
    }

    SECTION("\"ㅎ, ㄶ, ㅀ\" 뒤에 모음으로 시작된 어미나 접미사가 결합되는 경우에는 \"ㅎ\"을 발음하지 않는다")
    {
        const auto& current = defined(disassembleCompleteCharacter(L"많"));
        const auto& next = std::nullopt;

        const auto& result = transform12th(current, next);
        REQUIRE(result.current.choseong == L"ㅁ");
        REQUIRE(result.current.jungseong == L"ㅏ");
        REQUIRE(result.current.jongseong == L"ㄴ");

        REQUIRE(!result.next.has_value()); // As output type is Nullable<Syllable>
    }
}

} // namespace Rules
} // namespace StandardPronunciation
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz