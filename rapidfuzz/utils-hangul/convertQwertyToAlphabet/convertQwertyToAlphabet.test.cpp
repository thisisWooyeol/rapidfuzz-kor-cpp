#include "convertQwertyToAlphabet.hpp"
#include <catch2/catch_test_macros.hpp>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace ConvertQwertyToAlphabet {

TEST_CASE("convertQwertyToAlphabet", "[convertQwertyToAlphabet]")
{
    SECTION("영어 알파벳을 한글 음소로 바꾼다.")
    {
        REQUIRE(convertQwertyToAlphabet(L"abc") == L"ㅁㅠㅊ");
    }

    SECTION("쌍/자모음에 대응하지 않는 영어 알파벳을 한글 음소로 바꾼다.")
    {
        REQUIRE(convertQwertyToAlphabet(L"ABC") == L"ㅁㅠㅊ");
    }

    SECTION("영어 알파벳은 한글 음소로 바꾸고, 한글 음절은 유지한다.")
    {
        REQUIRE(convertQwertyToAlphabet(L"vm론트") == L"ㅍㅡ론트");
    }

    SECTION("분해된 한글 음소는 유지한다.")
    {
        REQUIRE(convertQwertyToAlphabet(L"ㅍㅡㄹㅗㄴㅌㅡ") == L"ㅍㅡㄹㅗㄴㅌㅡ");
    }

    SECTION("영어 알파벳이 아닌 입력은 유지한다.")
    {
        REQUIRE(convertQwertyToAlphabet(L"4월/20dlf!") == L"4월/20ㅇㅣㄹ!");
    }

    SECTION("영문 대문자는 쌍자/모음으로 바꾼다.")
    {
        REQUIRE(convertQwertyToAlphabet(L"RㅏㄱEㅜrl") == L"ㄲㅏㄱㄸㅜㄱㅣ");
        REQUIRE(convertQwertyToAlphabet(L"ㅇPdml") == L"ㅇㅖㅇㅡㅣ");
    }

    SECTION("빈 문자열은 빈 문자열을 반환한다.")
    {
        REQUIRE(convertQwertyToAlphabet(L"") == L"");
    }
}

TEST_CASE("convertQwertyToHangul", "[convertQwertyToHangul]")
{
    SECTION("영어 알파벳을 한글로 합성한다.")
    {
        REQUIRE(convertQwertyToHangul(L"abc") == L"뮻");
        REQUIRE(convertQwertyToHangul(L"vmfhsxmdpsem") == L"프론트엔드");
    }

    SECTION("쌍/자모음에 대응하지 않는 영어 알파벳을 한글로 합성한다.")
    {
        REQUIRE(convertQwertyToHangul(L"ABC") == L"뮻");
        REQUIRE(convertQwertyToHangul(L"VMFHSXM") == L"프론트");
    }

    SECTION("영어 알파벳은 한글로 합성하고, 한글 음절은 유지한다.")
    {
        REQUIRE(convertQwertyToHangul(L"vm론트") == L"프론트");
    }

    SECTION("인자가 한글 음소면 한글로 합성한다.")
    {
        REQUIRE(convertQwertyToHangul(L"ㅍㅡㄹㅗㄴㅌㅡ") == L"프론트");
    }

    SECTION("영문 대문자는 쌍자/모음에 대응하며 한글로 합성한다.")
    {
        REQUIRE(convertQwertyToHangul(L"RㅏㄱEㅜrl") == L"깍뚜기");
        REQUIRE(convertQwertyToHangul(L"ㅇPdml") == L"예의");
    }

    SECTION("빈 문자열은 빈 문자열을 반환한다.")
    {
        REQUIRE(convertQwertyToHangul(L"") == L"");
    }
}

} // namespace ConvertQwertyToAlphabet
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz
