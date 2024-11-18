#include "getChoseong.hpp"
#include <catch2/catch_test_macros.hpp>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace GetChoseong {

TEST_CASE("getChoseong", "[getChoseong]")
{
    SECTION("\"사과\" 단어에서 초성 \"ㅅㄱ\"을 추출한다.")
    {
        REQUIRE(getChoseong(L"사과") == L"ㅅㄱ");
    }

    SECTION("\"프론트엔드\" 단어에서 초성 \"ㅍㄹㅌㅇㄷ\"을 추출한다.")
    {
        REQUIRE(getChoseong(L"프론트엔드") == L"ㅍㄹㅌㅇㄷ");
    }

    SECTION("\"ㄴㅈ\" 문자에서 초성 \"ㄴㅈ\"을 추출한다.")
    {
        REQUIRE(getChoseong(L"ㄴㅈ") == L"ㄴㅈ");
    }

    SECTION("\"리액트\" 단어에서 초성 \"ㄹㅇㅌ\"을 추출한다.")
    {
        REQUIRE(getChoseong(L"리액트") == L"ㄹㅇㅌ");
    }

    SECTION("\"띄어 쓰기\" 문자열에서 초성 \"ㄸㅇ ㅆㄱ\"을 추출한다.")
    {
        REQUIRE(getChoseong(L"띄어 쓰기") == L"ㄸㅇ ㅆㄱ");
    }
}
} // namespace GetChoseong
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz