#include "power_consumption_calculator.hpp"
#include <gtest/gtest.h>

class PowerConsumptionCalcTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        std::string inputFile = R""""(
00100
11110
10110
10111
10101
01111
00111
11100
10000
11001
00010
01010
)"""";

        std::stringstream        ss(inputFile);
        std::string              line;
        std::vector<std::string> input;
        while(std::getline(ss, line, '\n'))
        {
            input.push_back(line);
        }

        calc = day_3::PowerConsumptionCalculator(input);
    }

    day_3::PowerConsumptionCalculator calc;
};

TEST_F(PowerConsumptionCalcTest, InputWorks)
{
    std::vector<day_3::PowerConsumptionCalculator::ReportLine> expectedResult {
        {false, false, true, false, false},
        {true, true, true, true, false},
        {true, false, true, true, false},
        {true, false, true, true, true},
        {true, false, true, false, true},
        {false, true, true, true, true},
        {false, false, true, true, true},
        {true, true, true, false, false},
        {true, false, false, false, false},
        {true, true, false, false, true},
        {false, false, false, true, false},
        {false, true, false, true, false},
    };

    EXPECT_EQ(calc.getFullReport(), expectedResult);
}

TEST_F(PowerConsumptionCalcTest, GetMostCommonBitTest)
{
    EXPECT_TRUE(calc.getMostCommonBit(0));
    EXPECT_FALSE(calc.getMostCommonBit(1));
    EXPECT_TRUE(calc.getMostCommonBit(2));
    EXPECT_TRUE(calc.getMostCommonBit(3));
    EXPECT_FALSE(calc.getMostCommonBit(4));
}

TEST_F(PowerConsumptionCalcTest, GetLeastCommonBitTest)
{
    EXPECT_FALSE(calc.getLeastCommonBit(0));
    EXPECT_TRUE(calc.getLeastCommonBit(1));
    EXPECT_FALSE(calc.getLeastCommonBit(2));
    EXPECT_FALSE(calc.getLeastCommonBit(3));
    EXPECT_TRUE(calc.getLeastCommonBit(4));
}