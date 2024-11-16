#include "hasBatchim.hpp"
#include <catch2/catch_test_macros.hpp>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace HasBatchim {

TEST_CASE("hasBatchim", "[hasBatchim]")
{
    SECTION("받침이 있다고 판단되는 경우")
    {
        SECTION("\"값\" 문자에서 받침이 있으므로 true를 반환한다.")
        {
            REQUIRE(hasBatchim(L"값") == true);
        }

        SECTION("\"공\" 문자에서 받침이 있으므로 true를 반환한다.")
        {
            REQUIRE(hasBatchim(L"공") == true);
        }

        SECTION("\"읊\" 문자에서 받침이 있으므로 true를 반환한다.")
        {
            REQUIRE(hasBatchim(L"읊") == true);
        }
    }

    SECTION("받침이 없다고 판단되는 경우")
    {
        SECTION("\"토\" 문자에서 받침이 없으므로 false를 반환한다.")
        {
            REQUIRE(hasBatchim(L"토") == false);
        }

        SECTION("\"서\" 문자에서 받침이 없으므로 false를 반환한다.")
        {
            REQUIRE(hasBatchim(L"서") == false);
        }

        SECTION("빈 문자열은 받침이 없으므로 false를 반환한다.")
        {
            REQUIRE(hasBatchim(L"") == false);
        }
    }

    SECTION("완성된 한글이 아닌 경우")
    {
        SECTION("한글이 자음 또는 모음으로만 구성된 경우 false를 반환한다.")
        {
            REQUIRE(hasBatchim(L"ㄱ") == false);
            REQUIRE(hasBatchim(L"ㅏ") == false);
        }

        SECTION("한글 외의 문자를 입력하면 false를 반환한다.")
        {
            REQUIRE(hasBatchim(L"cat") == false);
            REQUIRE(hasBatchim(L"!") == false);
        }
    }

    SECTION("홑받침")
    {
        SECTION("홑받침을 받으면 true를 반환한다.")
        {
            REQUIRE(hasBatchim(L"공", BatchimOptions{OnlyType::SINGLE}) == true);
            REQUIRE(hasBatchim(L"핫", BatchimOptions{OnlyType::SINGLE}) == true);
            REQUIRE(hasBatchim(L"양", BatchimOptions{OnlyType::SINGLE}) == true);
            REQUIRE(hasBatchim(L"신", BatchimOptions{OnlyType::SINGLE}) == true);
            REQUIRE(hasBatchim(L"확", BatchimOptions{OnlyType::SINGLE}) == true);
        }

        SECTION("홑받침이 아니라고 판단되는 경우")
        {
            SECTION("겹받침을 받으면 false를 반환한다.")
            {
                REQUIRE(hasBatchim(L"값", BatchimOptions{OnlyType::SINGLE}) == false);
                REQUIRE(hasBatchim(L"읊", BatchimOptions{OnlyType::SINGLE}) == false);
                REQUIRE(hasBatchim(L"웱", BatchimOptions{OnlyType::SINGLE}) == false);
            }

            SECTION("받침이 없는 문자를 받으면 false를 반환한다.")
            {
                REQUIRE(hasBatchim(L"토", BatchimOptions{OnlyType::SINGLE}) == false);
                REQUIRE(hasBatchim(L"서", BatchimOptions{OnlyType::SINGLE}) == false);
                REQUIRE(hasBatchim(L"와", BatchimOptions{OnlyType::SINGLE}) == false);
            }

            SECTION("한글 외의 문자를 입력하면 false를 반환한다.")
            {
                REQUIRE(hasBatchim(L"cat", BatchimOptions{OnlyType::SINGLE}) == false);
                REQUIRE(hasBatchim(L"", BatchimOptions{OnlyType::SINGLE}) == false);
                REQUIRE(hasBatchim(L"?", BatchimOptions{OnlyType::SINGLE}) == false);
            }
        }
    }

    SECTION("겹받침")
    {
        SECTION("겹받침을 받으면 true를 반환한다.")
        {
            REQUIRE(hasBatchim(L"값", BatchimOptions{OnlyType::DOUBLE}) == true);
            REQUIRE(hasBatchim(L"읊", BatchimOptions{OnlyType::DOUBLE}) == true);
            REQUIRE(hasBatchim(L"웱", BatchimOptions{OnlyType::DOUBLE}) == true);
        }

        SECTION("겹받침이 아니라고 판단되는 경우")
        {
            SECTION("홑받침을 받으면 false를 반환한다.")
            {
                REQUIRE(hasBatchim(L"공", BatchimOptions{OnlyType::DOUBLE}) == false);
                REQUIRE(hasBatchim(L"핫", BatchimOptions{OnlyType::DOUBLE}) == false);
                REQUIRE(hasBatchim(L"양", BatchimOptions{OnlyType::DOUBLE}) == false);
                REQUIRE(hasBatchim(L"신", BatchimOptions{OnlyType::DOUBLE}) == false);
                REQUIRE(hasBatchim(L"확", BatchimOptions{OnlyType::DOUBLE}) == false);
            }

            SECTION("받침이 없는 문자를 받으면 false를 반환한다.")
            {
                REQUIRE(hasBatchim(L"토", BatchimOptions{OnlyType::DOUBLE}) == false);
                REQUIRE(hasBatchim(L"서", BatchimOptions{OnlyType::DOUBLE}) == false);
                REQUIRE(hasBatchim(L"와", BatchimOptions{OnlyType::DOUBLE}) == false);
            }

            SECTION("한글 외의 문자를 입력하면 false를 반환한다.")
            {
                REQUIRE(hasBatchim(L"cat", BatchimOptions{OnlyType::DOUBLE}) == false);
                REQUIRE(hasBatchim(L"", BatchimOptions{OnlyType::DOUBLE}) == false);
                REQUIRE(hasBatchim(L"?", BatchimOptions{OnlyType::DOUBLE}) == false);
            }
        }
    }
}

} // namespace HasBatchim
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz