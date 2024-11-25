#include "romanize.hpp"
#include <catch2/catch_test_macros.hpp>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace Romanize {

TEST_CASE("romanize", "[romanize]")
{
    SECTION("자음 사이에서 동화 작용이 일어나는 경우")
    {
        REQUIRE(romanize(L"백마") == L"baengma");
        REQUIRE(romanize(L"종로") == L"jongno");
        REQUIRE(romanize(L"왕십리") == L"wangsimni");
        REQUIRE(romanize(L"별래") == L"byeollae");
        REQUIRE(romanize(L"신라") == L"silla");
    }

    SECTION("ㄴ, ㄹ’이 덧나는 경우")
    {
        REQUIRE(romanize(L"학여울") == L"hangnyeoul");
        REQUIRE(romanize(L"알약") == L"allyak");
    }

    SECTION("구개음화가 되는 경우")
    {
        REQUIRE(romanize(L"해돋이") == L"haedoji");
        REQUIRE(romanize(L"같이") == L"gachi");
        REQUIRE(romanize(L"굳히다") == L"guchida");
    }

    SECTION("\"ㄱ, ㄷ, ㅂ, ㅈ\"이 \"ㅎ\"과 합하여 거센소리로 소리 나는 경우")
    {
        REQUIRE(romanize(L"좋고") == L"joko");
        REQUIRE(romanize(L"놓다") == L"nota");
        REQUIRE(romanize(L"잡혀") == L"japyeo");
        REQUIRE(romanize(L"낳지") == L"nachi");
    }

    SECTION("된소리되기는 표기에 반영하지 않는다")
    {
        REQUIRE(romanize(L"압구정") == L"apgujeong");
        REQUIRE(romanize(L"낙동강") == L"nakdonggang");
        REQUIRE(romanize(L"죽변") == L"jukbyeon");
        REQUIRE(romanize(L"낙성대") == L"nakseongdae");
        REQUIRE(romanize(L"합정") == L"hapjeong");
        REQUIRE(romanize(L"팔당") == L"paldang");
        REQUIRE(romanize(L"샛별") == L"saetbyeol");
        REQUIRE(romanize(L"울산") == L"ulsan");
    }

    SECTION("\"ㄱ, ㄷ, ㅂ\"은 모음 앞에서는 \"g, d, b\"로, 자음 앞이나 어말에서는 \"k, t, p\"로 적는다")
    {
        REQUIRE(romanize(L"구미") == L"gumi");
        REQUIRE(romanize(L"영동") == L"yeongdong");
        REQUIRE(romanize(L"백암") == L"baegam");
        REQUIRE(romanize(L"옥천") == L"okcheon");
        REQUIRE(romanize(L"합덕") == L"hapdeok");
        REQUIRE(romanize(L"호법") == L"hobeop");
        REQUIRE(romanize(L"월곶") == L"wolgot");
        REQUIRE(romanize(L"벚꽃") == L"beotkkot");
        REQUIRE(romanize(L"한밭") == L"hanbat");
    }

    SECTION("\"ㄹ\"은 모음 앞에서는 \"r\"로, 자음 앞이나 어말에서는 \"l\"로 적는다. 단, \"ㄹㄹ\"은 \"ll\"로 "
            "적는다")
    {
        REQUIRE(romanize(L"구리") == L"guri");
        REQUIRE(romanize(L"설악") == L"seorak");
        REQUIRE(romanize(L"칠곡") == L"chilgok");
        REQUIRE(romanize(L"임실") == L"imsil");
        REQUIRE(romanize(L"울릉") == L"ulleung");
        REQUIRE(romanize(L"대관령") == L"daegwallyeong");
    }

    SECTION("완성된 음절이 아닌 경우에는 그대로 반환한다")
    {
        REQUIRE(romanize(L"ㄱ") == L"g");
        REQUIRE(romanize(L"가나다라ㅁㅂㅅㅇ") == L"ganadarambs");
        REQUIRE(romanize(L"ㅏ") == L"a");
        REQUIRE(romanize(L"ㅘ") == L"wa");
    }

    SECTION("특수문자는 로마자 표기로 변경하지 않는다")
    {
        REQUIRE(romanize(L"안녕하세요.") == L"annyeonghaseyo.");
        REQUIRE(romanize(L"한국어!") == L"hangugeo!");
        REQUIRE(romanize(L"") == L"");
        REQUIRE(romanize(L"!?/") == L"!?/");
    }

    SECTION("한글과 영어가 혼합된 경우에는 영어는 그대로 반환된다")
    {
        REQUIRE(romanize(L"안녕하세요 es-hangul") == L"annyeonghaseyo es-hangul");
        REQUIRE(romanize(L"한국은korea") == L"hangugeunkorea");
        REQUIRE(romanize(L"고양이는cat") == L"goyangineuncat");
    }
}
} // namespace Romanize
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz