#include "removeLastCharacter.hpp"
#include <catch2/catch_test_macros.hpp>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace RemoveLastCharacter {

TEST_CASE("removeLastCharacter", "[removeLastCharacter]")
{
    SECTION("마지막 문자가 겹받침인 경우 홑받침으로 바꾼다.")
    {
        REQUIRE(removeLastCharacter(L"안녕하세요 값") == L"안녕하세요 갑");
        REQUIRE(removeLastCharacter(L"안녕하세요 값이") == L"안녕하세요 값ㅇ");
    }

    SECTION("마지막 문자가 초성과 중성의 조합으로 끝날 경우 초성만 남긴다.")
    {
        REQUIRE(removeLastCharacter(L"프론트엔드") == L"프론트엔ㄷ");
        REQUIRE(removeLastCharacter(L"끓다") == L"끓ㄷ");
        REQUIRE(removeLastCharacter(L"관사") == L"관ㅅ");
        REQUIRE(removeLastCharacter(L"괴사") == L"괴ㅅ");
    }

    SECTION("마지막 문자가 초성과 중성과 종성의 조합으로 끝날 경우 초성과 중성이 조합된 문자만 남긴다.")
    {
        REQUIRE(removeLastCharacter(L"일요일") == L"일요이");
        REQUIRE(removeLastCharacter(L"완전") == L"완저");
        REQUIRE(removeLastCharacter(L"왅전") == L"왅저");
        REQUIRE(removeLastCharacter(L"깎") == L"까");
    }

    SECTION("마지막 문자가 초성과 중성의 조합으로 끝나며, 중성 입력 시 국제 표준 한글 레이아웃 기준 단일키로 "
            "처리되지 않는 이중모음 (ㅗ/ㅜ/ㅡ 계 이중모음) 인 경우 초성과 중성의 시작 모음만 남긴다.")
    {
        REQUIRE(removeLastCharacter(L"전화") == L"전호");
        REQUIRE(removeLastCharacter(L"예의") == L"예으");
        REQUIRE(removeLastCharacter(L"신세계") ==
                L"신세ㄱ"); // 'ㅖ'의 경우 단일키 처리가 가능한 이중모음이므로 모음이 남지 않는다.
    }

    SECTION("마지막 문자가 초성과 중성과 종성의 조합으로 끝나며, 중성 입력 시 국제 표준 한글 레이아웃 기준 "
            "단일키로 처리되지 않는 이중모음 (ㅗ/ㅜ/ㅡ 계 이중모음) 인 경우 초성과 중성만 남긴다.")
    {
        REQUIRE(removeLastCharacter(L"수확") == L"수화");
    }

    SECTION("마지막 문자가 초성과 중성과 종성의 조합으로 끝나며, 종성이 겹자음인 경우 초성과 중성과 종성의 "
            "시작 자음만 남긴다.")
    {
        REQUIRE(removeLastCharacter(L"끓") == L"끌");
    }

    SECTION("마지막 문자가 초성과 중성과 종성의 조합으로 끝나며, 중성 입력 시 국제 표준 한글 레이아웃 기준 "
            "단일키로 처리되지 않는 이중모음 (ㅗ/ㅜ/ㅡ 계 이중모음)이고 종성이 겹자음인 경우 초성과 중성과 "
            "종성의 시작 자음만 남긴다.")
    {
        REQUIRE(removeLastCharacter(L"왅") == L"완");
    }

    SECTION("빈 문자열일 경우 빈 문자열을 반환한다.")
    {
        REQUIRE(removeLastCharacter(L"") == L"");
    }
}
} // namespace RemoveLastCharacter
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz