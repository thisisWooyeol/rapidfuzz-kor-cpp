#include "numberToHangul.hpp"
#include <catch2/catch_test_macros.hpp>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace NumberToHangul {

TEST_CASE("numberToHangul", "[numberToHangul]")
{
    SECTION("기본 변환")
    {
        REQUIRE(numberToHangul(210000) == L"이십일만");
        REQUIRE(numberToHangul(12345) == L"일만이천삼백사십오");
        REQUIRE(numberToHangul(123456780) == L"일억이천삼백사십오만육천칠백팔십");
    }

    SECTION("공백 포함 변환")
    {
        REQUIRE(numberToHangul(210000, true) == L"이십일만");
        REQUIRE(numberToHangul(12345, true) == L"일만 이천삼백사십오");
        REQUIRE(numberToHangul(123456780, true) == L"일억 이천삼백사십오만 육천칠백팔십");
    }
}

TEST_CASE("numberToKoreanUpToThousand", "[numberToKoreanUpToThousand]")
{
    SECTION("0과 10,000보다 작은 경우")
    {
        REQUIRE(numberToHangul(0) == L"영");
        REQUIRE(numberToHangul(1) == L"일");
        REQUIRE(numberToHangul(2) == L"이");
        REQUIRE(numberToHangul(3) == L"삼");
        REQUIRE(numberToHangul(4) == L"사");
        REQUIRE(numberToHangul(5) == L"오");
        REQUIRE(numberToHangul(6) == L"육");
        REQUIRE(numberToHangul(7) == L"칠");
        REQUIRE(numberToHangul(8) == L"팔");
        REQUIRE(numberToHangul(9) == L"구");
        REQUIRE(numberToHangul(10) == L"십");
        REQUIRE(numberToHangul(11) == L"십일");
        REQUIRE(numberToHangul(20) == L"이십");
        REQUIRE(numberToHangul(30) == L"삼십");
        REQUIRE(numberToHangul(100) == L"백");
        REQUIRE(numberToHangul(101) == L"백일");
        REQUIRE(numberToHangul(110) == L"백십");
        REQUIRE(numberToHangul(200) == L"이백");
        REQUIRE(numberToHangul(300) == L"삼백");
        REQUIRE(numberToHangul(1000) == L"천");
        REQUIRE(numberToHangul(1001) == L"천일");
        REQUIRE(numberToHangul(1100) == L"천백");
        REQUIRE(numberToHangul(1200) == L"천이백");
        REQUIRE(numberToHangul(1234) == L"천이백삼십사");
        REQUIRE(numberToHangul(9999) == L"구천구백구십구");
    }
}
} // namespace NumberToHangul
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz