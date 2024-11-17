#include "disassemble.hpp"
#include <catch2/catch_test_macros.hpp>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace Disassemble {

TEST_CASE("disassembleToGroups", "[disassembleToGroups]")
{
    SECTION("값")
    {
        std::wstring input = L"값";
        std::vector<std::vector<std::wstring>> expected = {{L"ㄱ", L"ㅏ", L"ㅂ", L"ㅅ"}};
        REQUIRE(disassembleToGroups(input) == expected);
    }

    SECTION("값이 비싸다")
    {
        std::wstring input = L"값이 비싸다";
        std::vector<std::vector<std::wstring>> expected = {{L"ㄱ", L"ㅏ", L"ㅂ", L"ㅅ"},
                                                           {L"ㅇ", L"ㅣ"},
                                                           {L" "},
                                                           {L"ㅂ", L"ㅣ"},
                                                           {L"ㅆ", L"ㅏ"},
                                                           {L"ㄷ", L"ㅏ"}};
        REQUIRE(disassembleToGroups(input) == expected);
    }

    SECTION("사과 짱")
    {
        std::wstring input = L"사과 짱";
        std::vector<std::vector<std::wstring>> expected = {
            {L"ㅅ", L"ㅏ"}, {L"ㄱ", L"ㅗ", L"ㅏ"}, {L" "}, {L"ㅉ", L"ㅏ", L"ㅇ"}};
        REQUIRE(disassembleToGroups(input) == expected);
    }

    SECTION("ㄵ")
    {
        std::wstring input = L"ㄵ";
        std::vector<std::vector<std::wstring>> expected = {{L"ㄴ", L"ㅈ"}};
        REQUIRE(disassembleToGroups(input) == expected);
    }

    SECTION("ㅘ")
    {
        std::wstring input = L"ㅘ";
        std::vector<std::vector<std::wstring>> expected = {{L"ㅗ", L"ㅏ"}};
        REQUIRE(disassembleToGroups(input) == expected);
    }
}

TEST_CASE("disassemble", "[disassemble]")
{
    SECTION("값")
    {
        std::wstring input = L"값";
        std::wstring expected = L"ㄱㅏㅂㅅ";
        REQUIRE(disassemble(input) == expected);
    }

    SECTION("값이 비싸다")
    {
        std::wstring input = L"값이 비싸다";
        std::wstring expected = L"ㄱㅏㅂㅅㅇㅣ ㅂㅣㅆㅏㄷㅏ";
        REQUIRE(disassemble(input) == expected);
    }

    SECTION("사과 짱")
    {
        std::wstring input = L"사과 짱";
        std::wstring expected = L"ㅅㅏㄱㅗㅏ ㅉㅏㅇ";
        REQUIRE(disassemble(input) == expected);
    }

    SECTION("ㄵ")
    {
        std::wstring input = L"ㄵ";
        std::wstring expected = L"ㄴㅈ";
        REQUIRE(disassemble(input) == expected);
    }

    SECTION("ㅘ")
    {
        std::wstring input = L"ㅘ";
        std::wstring expected = L"ㅗㅏ";
        REQUIRE(disassemble(input) == expected);
    }
}

} // namespace Disassemble
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz
