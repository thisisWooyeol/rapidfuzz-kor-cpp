#include "standardPronunciation.hpp"
#include <catch2/catch_test_macros.hpp>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace StandardPronunciation {

TEST_CASE("standardizePronunciation", "[standardPronunciation]")
{
    SECTION("음절이 완성된 한글을 제외한 문자는 변경하지 않는다")
    {
        SECTION("단일 자모는 그대로 반환한다")
        {
            REQUIRE(standardizePronunciation(L"ㄱㄴㄷㄹㅏㅓㅑㅙ") == L"ㄱㄴㄷㄹㅏㅓㅑㅙ");
        }

        SECTION("특수문자는 그대로 반환한다")
        {
            REQUIRE(standardizePronunciation(L"!@#$%^&*()_+-=") == L"!@#$%^&*()_+-=");
        }

        SECTION("영어는 그대로 반환한다")
        {
            REQUIRE(standardizePronunciation(L"abcdefghijklmnopqrstuvwxyz") == L"abcdefghijklmnopqrstuvwxyz");
        }

        SECTION("숫자는 그대로 반환한다")
        {
            REQUIRE(standardizePronunciation(L"1234567890") == L"1234567890");
        }

        SECTION("빈 문자열은 그대로 반환한다")
        {
            REQUIRE(standardizePronunciation(L"") == L"");
        }
    }

    SECTION("한글은 음성 표기법으로 변경한다.")
    {

        SECTION("9항")
        {
            SECTION("받침 \"ㄲ, ㅋ\" / \"ㅅ, ㅆ, ㅈ, ㅊ, ㅌ\" / \"ㅍ\"은 어말 또는 자음 앞에서 각각 대표음 "
                    "\"ㄱ, ㄷ, ㅂ\"으로 발음한다")
            {
                REQUIRE(standardizePronunciation(L"닦다") == L"닥따");
                REQUIRE(standardizePronunciation(L"키읔") == L"키윽");

                REQUIRE(standardizePronunciation(L"옷") == L"옫");
                REQUIRE(standardizePronunciation(L"있다") == L"읻따");
                REQUIRE(standardizePronunciation(L"젖") == L"젇");
                REQUIRE(standardizePronunciation(L"빚다") == L"빋따");
                REQUIRE(standardizePronunciation(L"꽃") == L"꼳");
                REQUIRE(standardizePronunciation(L"솥") == L"솓");

                REQUIRE(standardizePronunciation(L"앞") == L"압");
                REQUIRE(standardizePronunciation(L"덮다") == L"덥따");
            }
        }

        SECTION("10항")
        {
            SECTION("겹받침 \"ㄳ\" / \"ㄵ\" / \"ㄼ, ㄽ, ㄾ\" / \"ㅄ\"은 어말 또는 자음 앞에서 각각 \"ㄱ, ㄴ, "
                    "ㄹ, ㅂ\"으로 발음한다")
            {
                REQUIRE(standardizePronunciation(L"넋") == L"넉");

                REQUIRE(standardizePronunciation(L"앉다") == L"안따");

                REQUIRE(standardizePronunciation(L"여덟") == L"여덜");
                REQUIRE(standardizePronunciation(L"외곬") == L"외골");
                REQUIRE(standardizePronunciation(L"핥다") == L"할따");

                REQUIRE(standardizePronunciation(L"값") == L"갑");
            }
        }

        SECTION("11항")
        {
            SECTION(
                "겹받침 \"ㄺ\" / \"ㄻ\" / \"ㄿ\"은 어말 또는 자음 앞에서 각각 \"ㄱ, ㅁ, ㅂ\"으로 발음한다")
            {
                REQUIRE(standardizePronunciation(L"닭") == L"닥");
                REQUIRE(standardizePronunciation(L"맑다") == L"막따");

                REQUIRE(standardizePronunciation(L"삶") == L"삼");
                REQUIRE(standardizePronunciation(L"젊다") == L"점따");

                REQUIRE(standardizePronunciation(L"읊고") == L"읍꼬");
                REQUIRE(standardizePronunciation(L"읊다") == L"읍따");
            }
        }

        SECTION("12항")
        {
            SECTION("\"ㅎ, ㄶ, ㅀ\" 뒤에 \"ㄱ, ㄷ, ㅈ\"이 결합되는 경우에는, 뒤 음절 첫소리와 합쳐서 \"ㅋ, "
                    "ㅌ, ㅊ\"으로 발음한다")
            {
                REQUIRE(standardizePronunciation(L"놓고") == L"노코");
                REQUIRE(standardizePronunciation(L"좋던") == L"조턴");
                REQUIRE(standardizePronunciation(L"쌓지") == L"싸치");
                REQUIRE(standardizePronunciation(L"많고") == L"만코");
                REQUIRE(standardizePronunciation(L"않던") == L"안턴");
                REQUIRE(standardizePronunciation(L"닳지") == L"달치");
            }

            SECTION("받침 \"ㄱ, ㄺ, ㄷ, ㅂ, ㄼ, ㅈ, ㄵ\"이 뒤 음절 첫소리 \"ㅎ\"과 결합되는 경우에도, 역시 "
                    "두 음을 합쳐서 \"ㅋ, ㅌ, ㅍ, ㅊ\"으로 발음한다")
            {
                REQUIRE(standardizePronunciation(L"각하") == L"가카");
                REQUIRE(standardizePronunciation(L"먹히다") == L"머키다");
                REQUIRE(standardizePronunciation(L"밝히다") == L"발키다");
                REQUIRE(standardizePronunciation(L"맏형") == L"마텽");
                REQUIRE(standardizePronunciation(L"좁히다") == L"조피다");
                REQUIRE(standardizePronunciation(L"넓히다") == L"널피다");
                REQUIRE(standardizePronunciation(L"꽂히다") == L"꼬치다");
                REQUIRE(standardizePronunciation(L"앉히다") == L"안치다");
            }

            SECTION("\"ㅎ, ㄶ, ㅀ\" 뒤에 \"ㅅ\"이 결합되는 경우에는, \"ㅅ\"을 \"ㅆ\"으로 발음한다")
            {
                REQUIRE(standardizePronunciation(L"닿소") == L"다쏘");
                REQUIRE(standardizePronunciation(L"많소") == L"만쏘");
                REQUIRE(standardizePronunciation(L"싫소") == L"실쏘");
            }

            SECTION("\"ㅎ\" 뒤에 \"ㄴ\"이 결합되는 경우에는 \"ㄴ\"으로 발음한다")
            {
                REQUIRE(standardizePronunciation(L"놓는") == L"논는");
                REQUIRE(standardizePronunciation(L"쌓네") == L"싼네");
            }

            SECTION("\"ㄶ, ㅀ\" 뒤에 \"ㄴ\"이 결합되는 경우에는, \"ㅎ\"을 발음하지 않는다")
            {
                REQUIRE(standardizePronunciation(L"않네") == L"안네");
                REQUIRE(standardizePronunciation(L"않는") == L"안는");
                REQUIRE(standardizePronunciation(L"뚫네") == L"뚤레");
                REQUIRE(standardizePronunciation(L"뚫는") == L"뚤른");
            }

            SECTION("\"ㅎ, ㄶ, ㅀ\" 뒤에 모음으로 시작된 어미나 접미사가 결합되는 경우에는 \"ㅎ\"을 발음하지 "
                    "않는다")
            {
                REQUIRE(standardizePronunciation(L"낳은") == L"나은");
                REQUIRE(standardizePronunciation(L"놓아") == L"노아");
                REQUIRE(standardizePronunciation(L"쌓이다") == L"싸이다");
                REQUIRE(standardizePronunciation(L"많아") == L"마나");
                REQUIRE(standardizePronunciation(L"않은") == L"아는");
                REQUIRE(standardizePronunciation(L"닳아") == L"다라");
                REQUIRE(standardizePronunciation(L"싫어도") == L"시러도");
            }

            SECTION("다음 음절이 없는 경우")
            {
                REQUIRE(standardizePronunciation(L"많") == L"만");
                REQUIRE(standardizePronunciation(L"싫") == L"실");
            }
        }

        SECTION("13항")
        {
            SECTION("홑받침이나 쌍받침이 모음으로 시작된 조사나 어미, 접미사와 결합되는 경우에는, 제 "
                    "음가대로 뒤 음절 첫소리로 옮겨 발음한다")
            {
                REQUIRE(standardizePronunciation(L"깎아") == L"까까");
                REQUIRE(standardizePronunciation(L"옷이") == L"오시");
                REQUIRE(standardizePronunciation(L"있어") == L"이써");
                REQUIRE(standardizePronunciation(L"낮이") == L"나지");
                REQUIRE(standardizePronunciation(L"앞으로") == L"아프로");
            }
        }

        SECTION("14항")
        {
            SECTION("겹받침이 모음으로 시작된 조사나 어미, 접미사와 결합되는 경우에는, 뒤엣것만을 뒤 음절 "
                    "첫소리로 옮겨 발음한다")
            {
                REQUIRE(standardizePronunciation(L"닭을") == L"달글");
                REQUIRE(standardizePronunciation(L"젊어") == L"절머");
                REQUIRE(standardizePronunciation(L"곬이") == L"골씨");
                REQUIRE(standardizePronunciation(L"핥아") == L"할타");
            }
        }

        SECTION("16항")
        {
            SECTION("한글 자모의 이름은 그 받침소리를 연음하되, \"ㄷ, ㅈ, ㅊ, ㅋ, ㅌ, ㅍ, ㅎ\"의 경우에는 "
                    "특별히 다음과 같이 발음한다")
            {
                REQUIRE(standardizePronunciation(L"디귿이") == L"디그시");
                REQUIRE(standardizePronunciation(L"지읒이") == L"지으시");
                REQUIRE(standardizePronunciation(L"치읓이") == L"치으시");
                REQUIRE(standardizePronunciation(L"키읔이") == L"키으기");
                REQUIRE(standardizePronunciation(L"티읕이") == L"티으시");
                REQUIRE(standardizePronunciation(L"피읖이") == L"피으비");
                REQUIRE(standardizePronunciation(L"히읗이") == L"히으시");
            }

            SECTION("자모의 이름이 \"ㄱ, ㄴ, ㄹ, ㅁ, ㅂ, ㅅ, ㅇ\"일 경우")
            {
                REQUIRE(standardizePronunciation(L"기역이") == L"기여기");
                REQUIRE(standardizePronunciation(L"니은이") == L"니으니");
                REQUIRE(standardizePronunciation(L"리을이") == L"리으리");
                REQUIRE(standardizePronunciation(L"미음이") == L"미으미");
                REQUIRE(standardizePronunciation(L"비읍이") == L"비으비");
                REQUIRE(standardizePronunciation(L"이응이") == L"이응이");
            }
        }

        SECTION("17항")
        {
            SECTION("받침 \"ㄷ\", \"ㅌ(ㄾ)\"이 조사나 접미사의 모음 \"ㅣ\"와 결합되는 경우에는, \"ㅈ\", "
                    "\"ㅊ\"으로 바꾸어서 뒤 음절 첫소리로 옮겨 발음한다")
            {
                REQUIRE(standardizePronunciation(L"곧이듣다") == L"고지듣따");
                REQUIRE(standardizePronunciation(L"굳이") == L"구지");
                REQUIRE(standardizePronunciation(L"미닫이") == L"미다지");
                REQUIRE(standardizePronunciation(L"땀받이") == L"땀바지");
                REQUIRE(standardizePronunciation(L"밭이") == L"바치");
                REQUIRE(standardizePronunciation(L"벼훑이") == L"벼훌치");
            }

            SECTION("\"ㄷ\" 뒤에 접미사 \"히\"가 결합되어 \"티\"를 이루는 것은 \"치\"로 발음한다")
            {
                REQUIRE(standardizePronunciation(L"굳히다") == L"구치다");
                REQUIRE(standardizePronunciation(L"닫히다") == L"다치다");
                REQUIRE(standardizePronunciation(L"묻히다") == L"무치다");
            }
        }

        SECTION("18항")
        {
            SECTION("받침 \"ㄱ, ㄲ, ㅋ, ㄳ, ㄺ\"일 경우")
            {
                REQUIRE(standardizePronunciation(L"먹는") == L"멍는");
                REQUIRE(standardizePronunciation(L"깎는") == L"깡는");
                REQUIRE(standardizePronunciation(L"키읔만") == L"키응만");
                REQUIRE(standardizePronunciation(L"몫몫이") == L"몽목씨");
                REQUIRE(standardizePronunciation(L"긁는") == L"긍는");
            }

            SECTION("받침 \"ㄷ, ㅅ, ㅆ, ㅈ, ㅊ, ㅌ, ㅎ\"일 경우")
            {
                REQUIRE(standardizePronunciation(L"닫는") == L"단는");
                REQUIRE(standardizePronunciation(L"짓는") == L"진는");
                REQUIRE(standardizePronunciation(L"있는") == L"인는");
                REQUIRE(standardizePronunciation(L"맞는") == L"만는");
                REQUIRE(standardizePronunciation(L"쫓는") == L"쫀는");
                REQUIRE(standardizePronunciation(L"붙는") == L"분는");
                REQUIRE(standardizePronunciation(L"놓는") == L"논는");
            }

            SECTION("받침 \"ㅂ, ㅍ, ㄼ, ㄿ, ㅄ\"일 경우")
            {
                REQUIRE(standardizePronunciation(L"잡는") == L"잠는");
                REQUIRE(standardizePronunciation(L"앞마당") == L"암마당");
                REQUIRE(standardizePronunciation(L"밟는") == L"밤는");
                REQUIRE(standardizePronunciation(L"읊는") == L"음는");
                REQUIRE(standardizePronunciation(L"없는") == L"엄는");
            }
        }

        SECTION("19항")
        {
            SECTION("받침 \"ㅁ, ㅇ\" 뒤에 연결되는 \"ㄹ\"은 \"ㄴ\"으로 발음한다")
            {
                REQUIRE(standardizePronunciation(L"담력") == L"담녁");
                REQUIRE(standardizePronunciation(L"침략") == L"침냑");
                REQUIRE(standardizePronunciation(L"강릉") == L"강능");
                REQUIRE(standardizePronunciation(L"항로") == L"항노");
                REQUIRE(standardizePronunciation(L"대통령") == L"대통녕");
            }

            SECTION("받침 \"ㄱ, ㅂ\" 뒤에 연결되는 \"ㄹ\"도 \"ㄴ\"으로 발음한다")
            {
                REQUIRE(standardizePronunciation(L"막론") == L"망논");
                REQUIRE(standardizePronunciation(L"석류") == L"성뉴");
                REQUIRE(standardizePronunciation(L"협력") == L"혐녁");
                REQUIRE(standardizePronunciation(L"법리") == L"범니");
            }
        }

        SECTION("20항")
        {
            SECTION("\"ㄴ\"은 \"ㄹ\"의 앞이나 뒤에서 \"ㄹ\"로 발음한다")
            {
                REQUIRE(standardizePronunciation(L"난로") == L"날로");
                REQUIRE(standardizePronunciation(L"신라") == L"실라");
                REQUIRE(standardizePronunciation(L"천리") == L"철리");
                REQUIRE(standardizePronunciation(L"대관령") == L"대괄령");
                REQUIRE(standardizePronunciation(L"칼날") == L"칼랄");
            }

            SECTION("첫소리 \"ㄴ\"이 \"ㅀ, ㄾ\" 뒤에 연결되는 경우에도 \"ㄹ\"로 발음한다")
            {
                REQUIRE(standardizePronunciation(L"닳는") == L"달른");
                REQUIRE(standardizePronunciation(L"핥네") == L"할레");
            }
        }

        SECTION("23항")
        {
            SECTION("받침 \"ㄱ(ㄲ, ㅋ, ㄳ, ㄺ), ㄷ(ㅅ, ㅆ, ㅈ, ㅊ, ㅌ), ㅂ(ㅍ, ㄼ, ㄿ, ㅄ)\" 뒤에 연결되는 "
                    "\"ㄱ, ㄷ, ㅂ, ㅅ, ㅈ\"은 된소리로 발음한다")
            {
                REQUIRE(standardizePronunciation(L"국밥") == L"국빱");
                REQUIRE(standardizePronunciation(L"깎다") == L"깍따");
                REQUIRE(standardizePronunciation(L"넋받이") == L"넉빠지");
                REQUIRE(standardizePronunciation(L"삯돈") == L"삭똔");
            }
        }

        SECTION("24항")
        {
            SECTION("어간 받침 \"ㄴ(ㄵ), ㅁ(ㄻ)\" 뒤에 결합되는 어미의 첫소리 \"ㄱ, ㄷ, ㅅ, ㅈ\"은 된소리로 "
                    "발음한다")
            {
                REQUIRE(standardizePronunciation(L"신고") == L"신꼬");
                REQUIRE(standardizePronunciation(L"껴안다") == L"껴안따");
                REQUIRE(standardizePronunciation(L"앉고") == L"안꼬");
                REQUIRE(standardizePronunciation(L"얹다") == L"언따");
                REQUIRE(standardizePronunciation(L"삼고") == L"삼꼬");
                REQUIRE(standardizePronunciation(L"더듬지") == L"더듬찌");
                REQUIRE(standardizePronunciation(L"닮고") == L"담꼬");
                REQUIRE(standardizePronunciation(L"젊지") == L"점찌");
            }
        }

        SECTION("25항")
        {
            SECTION(
                "어간 받침 \"ㄼ, ㄾ\" 뒤에 결합되는 어미의 첫소리 \"ㄱ, ㄷ, ㅅ, ㅈ\"은 된소리로 발음한다.")
            {
                REQUIRE(standardizePronunciation(L"넓게") == L"널께");
                REQUIRE(standardizePronunciation(L"핥다") == L"할따");
                REQUIRE(standardizePronunciation(L"훑소") == L"훌쏘");
                REQUIRE(standardizePronunciation(L"떫지") == L"떨찌");
            }
        }

        SECTION("\"ㄴ/ㄹ\"이 덧나는 경우")
        {
            SECTION("받침이 \"ㄱ, ㄴ, ㄷ, ㅁ, ㅂ, ㅇ\"이고 다음 음절이 \"야, 여, 요, 유, 이, 얘, 예\"로 "
                    "이어지는 경우")
            {
                REQUIRE(standardizePronunciation(L"학여울") == L"항녀울");
                REQUIRE(standardizePronunciation(L"맨입") == L"맨닙");
                REQUIRE(standardizePronunciation(L"담요") == L"담뇨");
                REQUIRE(standardizePronunciation(L"영업용") == L"영엄뇽");
                REQUIRE(standardizePronunciation(L"콩엿") == L"콩녇");
                REQUIRE(standardizePronunciation(L"알약") == L"알략");
            }

            SECTION("받침이 \"ㄹ\"이고 다음 음절이 \"야, 여, 요, 유, 이, 얘, 예\"로 이어지는 경우")
            {
                REQUIRE(standardizePronunciation(L"알약") == L"알략");
                REQUIRE(standardizePronunciation(L"서울역") == L"서울력");
                REQUIRE(standardizePronunciation(L"불여우") == L"불려우");
            }

            SECTION("ㄴ/ㄹ이 되기 위한 조건이지만 현재 음절의 중성의 ∙(아래아)가 하나가 아닐 경우에는 덧나지 "
                    "않고 연음규칙이 적용된다")
            {
                REQUIRE(standardizePronunciation(L"고양이") == L"고양이");
                REQUIRE(standardizePronunciation(L"윤여정") == L"윤녀정");
            }
        }
    }

    SECTION("경음화 등의 된소리를 적용하지 않는다")
    {
        SECTION("9항")
        {
            REQUIRE(standardizePronunciation(L"닦다", {false}) == L"닥다");
        }

        SECTION("10항")
        {
            REQUIRE(standardizePronunciation(L"앉다", {false}) == L"안다");
        }

        SECTION("11항")
        {
            REQUIRE(standardizePronunciation(L"맑다", {false}) == L"막다");
        }

        SECTION("17항")
        {
            REQUIRE(standardizePronunciation(L"곧이듣다", {false}) == L"고지듣다");
        }

        SECTION("23항")
        {
            REQUIRE(standardizePronunciation(L"국밥", {false}) == L"국밥");
        }

        SECTION("24항")
        {
            REQUIRE(standardizePronunciation(L"신고", {false}) == L"신고");
        }

        SECTION("25항")
        {
            REQUIRE(standardizePronunciation(L"넓게", {false}) == L"널게");
        }
    }
}
} // namespace StandardPronunciation
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz