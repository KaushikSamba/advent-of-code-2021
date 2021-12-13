#include "power_consumption_calculator.hpp"
#include <gtest/gtest.h>

TEST(BinaryConversionTest, Test1)
{
    EXPECT_EQ(day_3::PowerConsumptionCalculator::convertBinaryToDecimal({false, true, true, false, true}), 22);
    EXPECT_EQ(day_3::PowerConsumptionCalculator::convertBinaryToDecimal({true, false, false, true, false}), 9);
}

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
    EXPECT_TRUE(calc.getMostCommonBit(calc.getFullReport(), 0));
    EXPECT_FALSE(calc.getMostCommonBit(calc.getFullReport(), 1));
    EXPECT_TRUE(calc.getMostCommonBit(calc.getFullReport(), 2));
    EXPECT_TRUE(calc.getMostCommonBit(calc.getFullReport(), 3));
    EXPECT_FALSE(calc.getMostCommonBit(calc.getFullReport(), 4));
}

TEST_F(PowerConsumptionCalcTest, GetLeastCommonBitTest)
{
    EXPECT_FALSE(calc.getLeastCommonBit(calc.getFullReport(), 0));
    EXPECT_TRUE(calc.getLeastCommonBit(calc.getFullReport(), 1));
    EXPECT_FALSE(calc.getLeastCommonBit(calc.getFullReport(), 2));
    EXPECT_FALSE(calc.getLeastCommonBit(calc.getFullReport(), 3));
    EXPECT_TRUE(calc.getLeastCommonBit(calc.getFullReport(), 4));
}

TEST_F(PowerConsumptionCalcTest, CalcGammaRate)
{
    EXPECT_EQ(calc.calculateGammaRate(), 22);
}

TEST_F(PowerConsumptionCalcTest, CalcEpsilonRate)
{
    EXPECT_EQ(calc.calculateEpsilonRate(), 9);
}

TEST_F(PowerConsumptionCalcTest, CalcFinalAnswer)
{
    EXPECT_EQ(calc.calculatePowerConsumption(), 198);
}

TEST_F(PowerConsumptionCalcTest, CalcOxygenGeneratorRating)
{
    EXPECT_EQ(calc.calculateOxygenGeneratorRating(), 23);
}

TEST_F(PowerConsumptionCalcTest, CalcCo2ScrubberRating)
{
    EXPECT_EQ(calc.calculateCo2ScrubberRating(), 10);
}

TEST_F(PowerConsumptionCalcTest, CalcLifeSupportRating)
{
    EXPECT_EQ(calc.calculateLifeSupportRating(), 230);
}