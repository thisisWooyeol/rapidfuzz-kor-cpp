#include "hangul.hpp"
#include <catch2/catch_test_macros.hpp>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace _Internal {

TEST_CASE("isHangul*", "[isHangul]")
{
    SECTION("isHangulCharacter는 완성된 한글 문자를 받으면 true를 반환한다.")
    {
        REQUIRE(isHangulCharacter(L"가") == true);
        REQUIRE(isHangulCharacter(L"값") == true);
        REQUIRE(isHangulCharacter(L"ㄱ") == false);
        REQUIRE(isHangulCharacter(L"ㅏ") == false);
        REQUIRE(isHangulCharacter(L"a") == false);
    }

    SECTION("isHangulAlphabet은 조합되지않은 한글 문자를 받으면 true를 반환한다.")
    {
        REQUIRE(isHangulAlphabet(L"가") == false);
        REQUIRE(isHangulAlphabet(L"값") == false);
        REQUIRE(isHangulAlphabet(L"ㄱ") == true);
        REQUIRE(isHangulAlphabet(L"ㅏ") == true);
        REQUIRE(isHangulAlphabet(L"a") == false);
    }

    SECTION("isHangul은 한글 문자열을 받으면 true를 반환한다.")
    {
        REQUIRE(isHangul(L"값") == true);
        REQUIRE(isHangul(L"ㄱ") == true);
        REQUIRE(isHangul(L"ㅏ") == true);
        REQUIRE(isHangul(L"저는 고양이를 좋아합니다") == true);
        REQUIRE(isHangul(L"a") == false);
        REQUIRE(isHangul(L"111") == false);
        REQUIRE(isHangul(L"[111,111]") == false);
        REQUIRE(isHangul(L"{\"a\":111}") == false);
    }
}

TEST_CASE("parse", "[parse]")
{
    SECTION("parseHangul은 한글 문자열을 받으면 그대로 반환한다.")
    {
        REQUIRE(parseHangul(L"값") == L"값");
        REQUIRE(parseHangul(L"ㄱ") == L"ㄱ");
        REQUIRE(parseHangul(L"ㅏ") == L"ㅏ");
        REQUIRE(parseHangul(L"저는 고양이를 좋아합니다") == L"저는 고양이를 좋아합니다");
    }

    SECTION("parseHangul은 한글 문자열이 아닌 값을 받으면 에러를 발생시킨다.")
    {
        REQUIRE_THROWS(parseHangul(L"111"), "111 is not a valid hangul string");
        REQUIRE_THROWS(parseHangul(L"[111,111]"), "[111,111] is not a valid hangul string");
        REQUIRE_THROWS(parseHangul(L"{\"a\":111}"), "{\"a\":111} is not a valid hangul string");
    }

    SECTION("safeParseHangul은 한글 문자열을 받으면 성공 객체를 반환한다.")
    {
        auto result1 = safeParseHangul(L"값");
        REQUIRE(std::holds_alternative<SafeParseSuccess>(result1));
        REQUIRE(std::get<SafeParseSuccess>(result1).success == true);
        REQUIRE(std::get<SafeParseSuccess>(result1).data == L"값");

        auto result2 = safeParseHangul(L"ㄱ");
        REQUIRE(std::holds_alternative<SafeParseSuccess>(result2));
        REQUIRE(std::get<SafeParseSuccess>(result2).success == true);
        REQUIRE(std::get<SafeParseSuccess>(result2).data == L"ㄱ");

        auto result3 = safeParseHangul(L"ㅏ");
        REQUIRE(std::holds_alternative<SafeParseSuccess>(result3));
        REQUIRE(std::get<SafeParseSuccess>(result3).success == true);
        REQUIRE(std::get<SafeParseSuccess>(result3).data == L"ㅏ");

        auto result4 = safeParseHangul(L"저는 고양이를 좋아합니다");
        REQUIRE(std::holds_alternative<SafeParseSuccess>(result4));
        REQUIRE(std::get<SafeParseSuccess>(result4).success == true);
        REQUIRE(std::get<SafeParseSuccess>(result4).data == L"저는 고양이를 좋아합니다");
    }

    SECTION("safeParseHangul은 한글 문자열이 아닌 값을 받으면 실패 객체를 반환한다.")
    {
        auto result1 = safeParseHangul(L"111");
        REQUIRE(std::holds_alternative<SafeParseError>(result1));
        try {
            std::rethrow_exception(std::get<SafeParseError>(result1).error);
        }
        catch (const std::exception& e) {
            REQUIRE(std::string(e.what()) == "111 is not a valid hangul string");
        }

        auto result2 = safeParseHangul(L"[111,111]");
        REQUIRE(std::holds_alternative<SafeParseError>(result2));
        try {
            std::rethrow_exception(std::get<SafeParseError>(result2).error);
        }
        catch (const std::exception& e) {
            REQUIRE(std::string(e.what()) == "[111,111] is not a valid hangul string");
        }

        auto result3 = safeParseHangul(L"{\"a\":111}");
        REQUIRE(std::holds_alternative<SafeParseError>(result3));
        try {
            std::rethrow_exception(std::get<SafeParseError>(result3).error);
        }
        catch (const std::exception& e) {
            REQUIRE(std::string(e.what()) == "{\"a\":111} is not a valid hangul string");
        }
    }
}

TEST_CASE("binaryAssembleCharacters", "[binaryAssembleCharacters]")
{
    SECTION("초성과 중성만 조합")
    {
        REQUIRE(binaryAssembleCharacters(L"ㄱ", L"ㅏ") == L"가");
    }

    SECTION("초성과 중성이 합쳐진 문자와 종성을 조합")
    {
        REQUIRE(binaryAssembleCharacters(L"가", L"ㅇ") == L"강");
    }

    SECTION("초성과 중성과 종성이 합쳐진 문자와 자음을 조합하여 겹받침 만들기")
    {
        REQUIRE(binaryAssembleCharacters(L"갑", L"ㅅ") == L"값");
    }

    SECTION("초성과 중성이 합쳐진 문자와 모음을 조립하여 겹모음 만들기")
    {
        REQUIRE(binaryAssembleCharacters(L"고", L"ㅏ") == L"과");
    }

    SECTION("초성과 중성(겹모음)이 합쳐진 문자와 자음을 조합")
    {
        REQUIRE(binaryAssembleCharacters(L"과", L"ㄱ") == L"곽");
    }

    SECTION("초성과 중성과 종성이 합쳐진 문자와 자음을 조합하여 겹받침 만들기")
    {
        REQUIRE(binaryAssembleCharacters(L"완", L"ㅈ") == L"왅");
    }

    SECTION("모음만 있는 문자와 모음을 조합하여 겹모음 만들기")
    {
        REQUIRE(binaryAssembleCharacters(L"ㅗ", L"ㅏ") == L"ㅘ");
    }

    SECTION("초성과 중성과 종성이 합쳐진 문자의 연음 법칙")
    {
        REQUIRE(binaryAssembleCharacters(L"톳", L"ㅡ") == L"토스");
    }

    SECTION("초성과 종성(겹모음)과 종성이 합쳐진 문자의 연음 법칙")
    {
        REQUIRE(binaryAssembleCharacters(L"왅", L"ㅓ") == L"완저");
    }

    SECTION("초성과 중성과 종성(겹받침)이 합쳐진 문자의 연음 법칙")
    {
        REQUIRE(binaryAssembleCharacters(L"닭", L"ㅏ") == L"달가");
        REQUIRE(binaryAssembleCharacters(L"깎", L"ㅏ") == L"까까");
    }

    SECTION("문법에 맞지 않는 문자를 조합하면 단순 Join 한다. (문법 순서 틀림)")
    {
        REQUIRE(binaryAssembleCharacters(L"ㅏ", L"ㄱ") == L"ㅏㄱ");
        REQUIRE(binaryAssembleCharacters(L"까", L"ㅃ") == L"까ㅃ");
        REQUIRE(binaryAssembleCharacters(L"ㅘ", L"ㅏ") == L"ㅘㅏ");
    }

    SECTION("순서대로 입력했을 때 조합이 불가능한 문자라면 단순 Join 한다.")
    {
        REQUIRE(binaryAssembleCharacters(L"뼈", L"ㅣ") == L"뼈ㅣ");
    }

    SECTION("소스가 두 글자 이상이라면 Invalid source 에러를 발생시킨다.")
    {
        REQUIRE_THROWS(binaryAssembleCharacters(L"가나", L"ㄴ"),
                       "Invalid source character: 가나. Source must be one character.");
        REQUIRE_THROWS(binaryAssembleCharacters(L"ㄱㄴ", L"ㅏ"),
                       "Invalid source character: ㄱㄴ. Source must be one character.");
    }

    SECTION("다음 문자가 한글 문자 한 글자가 아니라면 Invalid next character 에러를 발생시킨다.")
    {
        REQUIRE_THROWS(binaryAssembleCharacters(L"ㄱ", L"a"),
                       "Invalid next character: a. Next character must be one of the choseong, "
                       "jungseong, or jongseong.");
        REQUIRE_THROWS(binaryAssembleCharacters(L"ㄱ", L"ㅡㅏ"),
                       "Invalid next character: ㅡㅏ. Next character must be one of the choseong, "
                       "jungseong, or jongseong.");
    }
}

TEST_CASE("binaryAssemble", "[binaryAssemble]")
{
    SECTION("문장과 모음을 조합하여 다음 글자를 생성한다.")
    {
        REQUIRE(binaryAssemble(L"저는 고양이를 좋아합닏", L"ㅏ") == L"저는 고양이를 좋아합니다");
    }

    SECTION("문장과 자음을 조합하여 홑받침을 생성한다.")
    {
        REQUIRE(binaryAssemble(L"저는 고양이를 좋아하", L"ㅂ") == L"저는 고양이를 좋아합");
    }

    SECTION("문장과 자음을 조합하여 겹받침을 생성한다.")
    {
        REQUIRE(binaryAssemble(L"저는 고양이를 좋아합", L"ㅅ") == L"저는 고양이를 좋아핪");
    }

    SECTION("조합이 불가능한 자음이 입력되면 단순 Join 한다.")
    {
        REQUIRE(binaryAssemble(L"저는 고양이를 좋아합", L"ㄲ") == L"저는 고양이를 좋아합ㄲ");
        REQUIRE(binaryAssemble(L"저는 고양이를 좋아합", L"ㅂ") == L"저는 고양이를 좋아합ㅂ");
    }

    SECTION("조합이 불가능한 모음이 입력되면 단순 Join 한다.")
    {
        REQUIRE(binaryAssemble(L"저는 고양이를 좋아하", L"ㅏ") == L"저는 고양이를 좋아하ㅏ");
        REQUIRE(binaryAssemble(L"저는 고양이를 좋아합니다", L"ㅜ") == L"저는 고양이를 좋아합니다ㅜ");
    }

    SECTION("assertHangul")
    {
        SECTION("한글 문자열을 받으면 에러를 발생시키지 않는다.")
        {
            REQUIRE_NOTHROW(assertHangul(L"ㄱ"));
            REQUIRE_NOTHROW(assertHangul(L"고양이"));
            REQUIRE_NOTHROW(assertHangul(L"저는 고양이를 좋아합니다"));
            REQUIRE_NOTHROW(assertHangul(L"저는 고양이를 좋아합니ㄷ"));
        }

        SECTION("한글 문자열이 아닌 값을 받으면 '___ is not a valid hangul string' 에러를 발생시킨다.")
        {
            REQUIRE_THROWS(assertHangul(L"aaaaaa"), "\"aaaaaa\" is not a valid hangul string");
            REQUIRE_THROWS(assertHangul(L"111"), "111 is not a valid hangul string");
            REQUIRE_THROWS(assertHangul(L"[111,111]"), "[111,111] is not a valid hangul string");
            REQUIRE_THROWS(assertHangul(L"{\"a\":111}"), "{\"a\":111} is not a valid hangul string");
        }
    }
}

} // namespace _Internal
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz
