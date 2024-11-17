#include "josa.hpp"
#include <catch2/catch_test_macros.hpp>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace Josa {

TEST_CASE("josa", "[josa]")
{
    SECTION("주격조사")
    {
        REQUIRE(josa(L"샴푸", JosaOption::이_가) == L"샴푸가");
        REQUIRE(josa(L"칫솔", JosaOption::이_가) == L"칫솔이");
    }

    SECTION("목적격조사")
    {
        REQUIRE(josa(L"샴푸", JosaOption::을_를) == L"샴푸를");
        REQUIRE(josa(L"칫솔", JosaOption::을_를) == L"칫솔을");
    }

    SECTION("대조의 보조사")
    {
        REQUIRE(josa(L"샴푸", JosaOption::은_는) == L"샴푸는");
        REQUIRE(josa(L"칫솔", JosaOption::은_는) == L"칫솔은");
    }

    SECTION("방향의 격조사")
    {
        REQUIRE(josa(L"바깥", JosaOption::으로_로) == L"바깥으로");
        REQUIRE(josa(L"내부", JosaOption::으로_로) == L"내부로");
    }

    SECTION("방향의 격조사 ㄹ 받침 예외 처리")
    {
        REQUIRE(josa(L"지름길", JosaOption::으로_로) == L"지름길로");
    }

    SECTION("비교의 격조사")
    {
        REQUIRE(josa(L"샴푸", JosaOption::와_과) == L"샴푸와");
        REQUIRE(josa(L"칫솔", JosaOption::와_과) == L"칫솔과");
    }

    SECTION("선택의 보조사")
    {
        REQUIRE(josa(L"샴푸", JosaOption::이나_나) == L"샴푸나");
        REQUIRE(josa(L"칫솔", JosaOption::이나_나) == L"칫솔이나");
    }

    SECTION("화제의 보조사")
    {
        REQUIRE(josa(L"샴푸", JosaOption::이란_란) == L"샴푸란");
        REQUIRE(josa(L"칫솔", JosaOption::이란_란) == L"칫솔이란");
    }

    SECTION("호격조사")
    {
        REQUIRE(josa(L"철수", JosaOption::아_야) == L"철수야");
        REQUIRE(josa(L"길동", JosaOption::아_야) == L"길동아");
    }

    SECTION("접속조사")
    {
        REQUIRE(josa(L"고기", JosaOption::이랑_랑) == L"고기랑");
        REQUIRE(josa(L"과일", JosaOption::이랑_랑) == L"과일이랑");
    }

    SECTION("주제의 보조사")
    {
        REQUIRE(josa(L"의사", JosaOption::이라_라) == L"의사라");
        REQUIRE(josa(L"선생님", JosaOption::이라_라) == L"선생님이라");
    }

    SECTION("서울격조사와 종결어미")
    {
        REQUIRE(josa(L"사과", JosaOption::이에요_예요) == L"사과예요");
        REQUIRE(josa(L"책", JosaOption::이에요_예요) == L"책이에요");
    }

    SECTION("서술격조사와 종결어미, \"이\"로 끝나는 단어 예외 처리")
    {
        REQUIRE(josa(L"때밀이", JosaOption::이에요_예요) == L"때밀이예요");
    }

    SECTION("지위나 신분 또는 자격을 나타내는 위격조사")
    {
        REQUIRE(josa(L"학생", JosaOption::으로서_로서) == L"학생으로서");
        REQUIRE(josa(L"부모", JosaOption::으로서_로서) == L"부모로서");
    }

    SECTION("지위나 신분 또는 자격을 나타내는 위격조사 ㄹ 받침 예외 처리")
    {
        REQUIRE(josa(L"라이벌", JosaOption::으로서_로서) == L"라이벌로서");
    }

    SECTION("수단의 의미를 나타내는 도구격조사")
    {
        REQUIRE(josa(L"토큰", JosaOption::으로써_로써) == L"토큰으로써");
        REQUIRE(josa(L"함수", JosaOption::으로써_로써) == L"함수로써");
    }

    SECTION("수단의 의미를 나타내는 도구격조사 ㄹ 받침 예외 처리")
    {
        REQUIRE(josa(L"건물", JosaOption::으로써_로써) == L"건물로써");
    }

    SECTION("어떤 행동의 출발점이나 비롯되는 대상임을 나타내는 격 조사")
    {
        REQUIRE(josa(L"역삼동", JosaOption::으로부터_로부터) == L"역삼동으로부터");
        REQUIRE(josa(L"저기", JosaOption::으로부터_로부터) == L"저기로부터");
    }

    SECTION("어떤 행동의 출발점이나 비롯되는 대상임을 나타내는 격 조사 ㄹ 받침 예외 처리")
    {
        REQUIRE(josa(L"동굴", JosaOption::으로부터_로부터) == L"동굴로부터");
    }

    SECTION("단어가 빈 문자열인 경우 빈 문자열을 반환한다.")
    {
        REQUIRE(josa(L"", JosaOption::이_가) == L"");
        REQUIRE(josa(L"", JosaOption::을_를) == L"");
        REQUIRE(josa(L"", JosaOption::은_는) == L"");
        REQUIRE(josa(L"", JosaOption::으로_로) == L"");
        REQUIRE(josa(L"", JosaOption::와_과) == L"");
        REQUIRE(josa(L"", JosaOption::이나_나) == L"");
        REQUIRE(josa(L"", JosaOption::이란_란) == L"");
        REQUIRE(josa(L"", JosaOption::아_야) == L"");
        REQUIRE(josa(L"", JosaOption::이랑_랑) == L"");
        REQUIRE(josa(L"", JosaOption::이에요_예요) == L"");
        REQUIRE(josa(L"", JosaOption::으로서_로서) == L"");
        REQUIRE(josa(L"", JosaOption::으로써_로써) == L"");
        REQUIRE(josa(L"", JosaOption::으로부터_로부터) == L"");
        REQUIRE(josa(L"", JosaOption::이라_라) == L"");
    }
}

TEST_CASE("josaPicker", "[josaPicker]")
{
    SECTION("첫 번째 매개변수가 빈 문자열이라면 옵션 중 첫 번째 값을 반환한다.")
    {
        REQUIRE(josaPicker(L"", JosaOption::이_가) == L"이");
        REQUIRE(josaPicker(L"", JosaOption::을_를) == L"을");
        REQUIRE(josaPicker(L"", JosaOption::은_는) == L"은");
        REQUIRE(josaPicker(L"", JosaOption::으로_로) == L"으로");
        REQUIRE(josaPicker(L"", JosaOption::와_과) == L"와");
        REQUIRE(josaPicker(L"", JosaOption::이나_나) == L"이나");
        REQUIRE(josaPicker(L"", JosaOption::이란_란) == L"이란");
        REQUIRE(josaPicker(L"", JosaOption::아_야) == L"아");
        REQUIRE(josaPicker(L"", JosaOption::이랑_랑) == L"이랑");
        REQUIRE(josaPicker(L"", JosaOption::이에요_예요) == L"이에요");
        REQUIRE(josaPicker(L"", JosaOption::으로서_로서) == L"으로서");
        REQUIRE(josaPicker(L"", JosaOption::으로써_로써) == L"으로써");
        REQUIRE(josaPicker(L"", JosaOption::으로부터_로부터) == L"으로부터");
        REQUIRE(josaPicker(L"", JosaOption::이라_라) == L"이라");
    }

    SECTION("주격조사")
    {
        REQUIRE(josaPicker(L"샴푸", JosaOption::이_가) == L"가");
        REQUIRE(josaPicker(L"칫솔", JosaOption::이_가) == L"이");
    }

    SECTION("목적격조사")
    {
        REQUIRE(josaPicker(L"샴푸", JosaOption::을_를) == L"를");
        REQUIRE(josaPicker(L"칫솔", JosaOption::을_를) == L"을");
    }

    SECTION("대조의 보조사")
    {
        REQUIRE(josaPicker(L"샴푸", JosaOption::은_는) == L"는");
        REQUIRE(josaPicker(L"칫솔", JosaOption::은_는) == L"은");
    }

    SECTION("방향의 격조사")
    {
        REQUIRE(josaPicker(L"바깥", JosaOption::으로_로) == L"으로");
        REQUIRE(josaPicker(L"내부", JosaOption::으로_로) == L"로");
    }

    SECTION("방향의 격조사 ㄹ 받침 예외 처리")
    {
        REQUIRE(josaPicker(L"지름길", JosaOption::으로_로) == L"로");
    }

    SECTION("비교의 격조사")
    {
        REQUIRE(josaPicker(L"샴푸", JosaOption::와_과) == L"와");
        REQUIRE(josaPicker(L"칫솔", JosaOption::와_과) == L"과");
    }

    SECTION("선택의 보조사")
    {
        REQUIRE(josaPicker(L"샴푸", JosaOption::이나_나) == L"나");
        REQUIRE(josaPicker(L"칫솔", JosaOption::이나_나) == L"이나");
    }

    SECTION("화제의 보조사")
    {
        REQUIRE(josaPicker(L"샴푸", JosaOption::이란_란) == L"란");
        REQUIRE(josaPicker(L"칫솔", JosaOption::이란_란) == L"이란");
    }

    SECTION("호격조사")
    {
        REQUIRE(josaPicker(L"철수", JosaOption::아_야) == L"야");
        REQUIRE(josaPicker(L"길동", JosaOption::아_야) == L"아");
    }

    SECTION("접속조사")
    {
        REQUIRE(josaPicker(L"고기", JosaOption::이랑_랑) == L"랑");
        REQUIRE(josaPicker(L"과일", JosaOption::이랑_랑) == L"이랑");
    }

    SECTION("주제의 보조사")
    {
        REQUIRE(josaPicker(L"의사", JosaOption::이라_라) == L"라");
        REQUIRE(josaPicker(L"선생님", JosaOption::이라_라) == L"이라");
    }

    SECTION("서울격조사와 종결어미")
    {
        REQUIRE(josaPicker(L"사과", JosaOption::이에요_예요) == L"예요");
        REQUIRE(josaPicker(L"책", JosaOption::이에요_예요) == L"이에요");
    }

    SECTION("서술격조사와 종결어미, \"이\"로 끝나는 단어 예외 처리")
    {
        REQUIRE(josaPicker(L"때밀이", JosaOption::이에요_예요) == L"예요");
    }

    SECTION("지위나 신분 또는 자격을 나타내는 위격조사")
    {
        REQUIRE(josaPicker(L"학생", JosaOption::으로서_로서) == L"으로서");
        REQUIRE(josaPicker(L"부모", JosaOption::으로서_로서) == L"로서");
    }

    SECTION("지위나 신분 또는 자격을 나타내는 위격조사 ㄹ 받침 예외 처리")
    {
        REQUIRE(josaPicker(L"라이벌", JosaOption::으로서_로서) == L"로서");
    }

    SECTION("수단의 의미를 나타내는 도구격조사")
    {
        REQUIRE(josaPicker(L"토큰", JosaOption::으로써_로써) == L"으로써");
        REQUIRE(josaPicker(L"함수", JosaOption::으로써_로써) == L"로써");
    }

    SECTION("수단의 의미를 나타내는 도구격조사 ㄹ 받침 예외 처리")
    {
        REQUIRE(josaPicker(L"건물", JosaOption::으로써_로써) == L"로써");
    }

    SECTION("어떤 행동의 출발점이나 비롯되는 대상임을 나타내는 격 조사")
    {
        REQUIRE(josaPicker(L"역삼동", JosaOption::으로부터_로부터) == L"으로부터");
        REQUIRE(josaPicker(L"저기", JosaOption::으로부터_로부터) == L"로부터");
    }

    SECTION("어떤 행동의 출발점이나 비롯되는 대상임을 나타내는 격 조사 ㄹ 받침 예외 처리")
    {
        REQUIRE(josaPicker(L"동굴", JosaOption::으로부터_로부터) == L"로부터");
    }
}
} // namespace Josa
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz