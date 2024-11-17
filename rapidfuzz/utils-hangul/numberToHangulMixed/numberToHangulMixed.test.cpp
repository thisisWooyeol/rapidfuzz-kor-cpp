#include "numberToHangulMixed.hpp"
#include <catch2/catch_test_macros.hpp>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace NumberToHangulMixed {

TEST_CASE("numberToHangulMixed", "[numberToHangulMixed]")
{
    SECTION("기본 변환")
    {
        REQUIRE(numberToHangulMixed(210000) == L"21만");
        REQUIRE(numberToHangulMixed(12345) == L"1만2,345");
        REQUIRE(numberToHangulMixed(123456780) == L"1억2,345만6,780");
    }

    SECTION("공백 포함 변환")
    {
        REQUIRE(numberToHangulMixed(210000, true) == L"21만");
        REQUIRE(numberToHangulMixed(12345, true) == L"1만 2,345");
        REQUIRE(numberToHangulMixed(123456780, true) == L"1억 2,345만 6,780");
    }

    SECTION("0과 10,000보다 작은 경우")
    {
        REQUIRE(numberToHangulMixed(0) == L"0");
        REQUIRE(numberToHangulMixed(1) == L"1");
        REQUIRE(numberToHangulMixed(2) == L"2");
        REQUIRE(numberToHangulMixed(3) == L"3");
        REQUIRE(numberToHangulMixed(4) == L"4");
        REQUIRE(numberToHangulMixed(5) == L"5");
        REQUIRE(numberToHangulMixed(6) == L"6");
        REQUIRE(numberToHangulMixed(7) == L"7");
        REQUIRE(numberToHangulMixed(8) == L"8");
        REQUIRE(numberToHangulMixed(9) == L"9");
        REQUIRE(numberToHangulMixed(10) == L"10");
        REQUIRE(numberToHangulMixed(11) == L"11");
        REQUIRE(numberToHangulMixed(20) == L"20");
        REQUIRE(numberToHangulMixed(30) == L"30");
        REQUIRE(numberToHangulMixed(100) == L"100");
        REQUIRE(numberToHangulMixed(101) == L"101");
        REQUIRE(numberToHangulMixed(110) == L"110");
        REQUIRE(numberToHangulMixed(200) == L"200");
        REQUIRE(numberToHangulMixed(300) == L"300");
        REQUIRE(numberToHangulMixed(1000) == L"1,000");
        REQUIRE(numberToHangulMixed(1001) == L"1,001");
        REQUIRE(numberToHangulMixed(1100) == L"1,100");
        REQUIRE(numberToHangulMixed(1200) == L"1,200");
        REQUIRE(numberToHangulMixed(1234) == L"1,234");
        REQUIRE(numberToHangulMixed(9999) == L"9,999");
    }
}
} // namespace NumberToHangulMixed
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz