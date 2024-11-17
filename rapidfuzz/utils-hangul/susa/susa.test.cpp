#include "susa.hpp"
#include <catch2/catch_test_macros.hpp>

namespace RapidFuzz {
namespace Utils {
namespace Hangul {
namespace Susa {

TEST_CASE("susa", "[susa]")
{
    struct TestCase {
        int num;
        std::wstring word;
        std::wstring classifier;
    };

    std::vector<TestCase> validTestCases{
        {1, L"하나", L"한"},      {2, L"둘", L"두"},
        {3, L"셋", L"세"},        {4, L"넷", L"네"},
        {5, L"다섯", L"다섯"},    {6, L"여섯", L"여섯"},
        {7, L"일곱", L"일곱"},    {8, L"여덟", L"여덟"},
        {9, L"아홉", L"아홉"},    {10, L"열", L"열"},
        {11, L"열하나", L"열한"}, {12, L"열둘", L"열두"},
        {20, L"스물", L"스무"},   {21, L"스물하나", L"스물한"},
        {30, L"서른", L"서른"},   {99, L"아흔아홉", L"아흔아홉"},
        {100, L"백", L"백"},
    };

    std::vector<int> invalidTestCases{
        -1,
        0,
        101,
    };

    SECTION("유효한 숫자에 대한 수사 변환")
    {
        for (const auto& testCase : validTestCases) {
            SECTION(std::to_string(testCase.num) + " - 순 우리말 수사로 바꿔 반환해야 한다.")
            {
                REQUIRE(susa(testCase.num) == testCase.word);
            }

            SECTION(std::to_string(testCase.num) +
                    " -순 우리말 수 관형사가 있다면 수 관형사로 없다면 수사로 반환해야 한다.")
            {
                REQUIRE(susa(testCase.num, true) == testCase.classifier);
            }
        }
    }

    SECTION("유효하지 않은 숫자에 대한 수사 변환")
    {
        for (const auto& invalidNum : invalidTestCases) {
            SECTION("유효하지 않은 숫자 " + std::to_string(invalidNum) + "에 대해 오류를 발생시켜야 한다.")
            {
                REQUIRE_THROWS(susa(invalidNum), "지원하지 않는 숫자입니다.");
                REQUIRE_THROWS(susa(invalidNum, true), "지원하지 않는 숫자입니다.");
            }
        }
    }
}
} // namespace Susa
} // namespace Hangul
} // namespace Utils
} // namespace RapidFuzz