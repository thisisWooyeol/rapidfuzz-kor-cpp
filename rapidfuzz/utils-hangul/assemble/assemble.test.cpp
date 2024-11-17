#include "assemble.hpp"
#include <catch2/catch_test_macros.hpp>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace Assemble {

TEST_CASE("assemble", "[assemble]")
{
    SECTION("온전한 한글과 한글 문자 조합")
    {
        std::vector<std::wstring> input = {L"아버지가", L" ", L"방ㅇ", L"ㅔ ", L"들ㅇ", L"ㅓ갑니다"};
        std::wstring expected = L"아버지가 방에 들어갑니다";
        std::wstring result = assemble(input);
        REQUIRE(result == expected);
    }

    SECTION("온전한 한글만 조합")
    {
        std::vector<std::wstring> input = {L"아버지가", L" ", L"방에 ", L"들어갑니다"};
        std::wstring expected = L"아버지가 방에 들어갑니다";
        std::wstring result = assemble(input);
        REQUIRE(result == expected);
    }

    SECTION("온전하지 않은 한글만 조합")
    {
        std::vector<std::wstring> input = {L"ㅇ", L"ㅏ", L"ㅂ", L"ㅓ", L"ㅈ", L"ㅣ"};
        std::wstring expected = L"아버지";
        std::wstring result = assemble(input);
        REQUIRE(result == expected);
    }

    SECTION("빈 입력 테스트")
    {
        std::vector<std::wstring> input = {};
        std::wstring expected = L"";
        std::wstring result = assemble(input);
        REQUIRE(result == expected);
    }
}

} // namespace Assemble
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz
