#include "disassembleCompleteCharacter.hpp"
#include <catch2/catch_test_macros.hpp>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace DisassembleCompleteCharacter {

TEST_CASE("disassembleCompleteCharacter", "[disassembleCompleteCharacter]")
{
    SECTION("값")
    {
        std::wstring input = L"값";
        std::optional<DisassembledCharacter> result = disassembleCompleteCharacter(input);

        REQUIRE(result.has_value() == true);
        REQUIRE(result->choseong == L"ㄱ");
        REQUIRE(result->jungseong == L"ㅏ");
        REQUIRE(result->jongseong == L"ㅂㅅ");
    }

    SECTION("리")
    {
        std::wstring input = L"리";
        std::optional<DisassembledCharacter> result = disassembleCompleteCharacter(input);

        REQUIRE(result.has_value() == true);
        REQUIRE(result->choseong == L"ㄹ");
        REQUIRE(result->jungseong == L"ㅣ");
        REQUIRE(result->jongseong.empty() == true);
    }

    SECTION("빚")
    {
        std::wstring input = L"빚";
        std::optional<DisassembledCharacter> result = disassembleCompleteCharacter(input);

        REQUIRE(result.has_value() == true);
        REQUIRE(result->choseong == L"ㅂ");
        REQUIRE(result->jungseong == L"ㅣ");
        REQUIRE(result->jongseong == L"ㅈ");
    }

    SECTION("박")
    {
        std::wstring input = L"박";
        std::optional<DisassembledCharacter> result = disassembleCompleteCharacter(input);

        REQUIRE(result.has_value() == true);
        REQUIRE(result->choseong == L"ㅂ");
        REQUIRE(result->jungseong == L"ㅏ");
        REQUIRE(result->jongseong == L"ㄱ");
    }

    SECTION("완전한 한글 문자열이 아니면 optional none을 반환해야 합니다.")
    {
        std::wstring input1 = L"ㄱ";
        std::optional<DisassembledCharacter> result1 = disassembleCompleteCharacter(input1);
        REQUIRE(result1.has_value() == false);

        std::wstring input2 = L"ㅏ";
        std::optional<DisassembledCharacter> result2 = disassembleCompleteCharacter(input2);
        REQUIRE(result2.has_value() == false);
    }
}

} // namespace DisassembleCompleteCharacter
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz
