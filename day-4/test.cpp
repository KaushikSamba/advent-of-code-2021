#include "bingo_player.hpp"
#include "utils/input_parser.hpp"
#include <gtest/gtest.h>

class BingoPlayerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        std::string inputFile = R""""(7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1

22 13 17 11  0
 8  2 23  4 24
21  9 14 16  7
 6 10  3 18  5
 1 12 20 15 19

 3 15  0  2 22
 9 18 13 17  5
19  8  7 25 23
20 11 10 24  4
14 21 16 12  6

14 21 17 24  4
10 16 15  9 19
18  8 23 26 20
22 11 13  6  5
2  0 12  3  7
)"""";

        std::stringstream ss(inputFile);
        std::string       line;
        // The first line is comma separated, gives the list of numbers:
        std::getline(ss, line, '\n');

        // Parse the list of numbers
        std::stringstream numberListStream {line};
        listOfNumbers = utils::parsing::parseCommaSeparatedLine<unsigned int>(numberListStream);
        // Second line is empty
        std::getline(ss, line, '\n');

        // Parse the boards
        listOfBoards =
            utils::parsing::parseNewLineSeparatedInputs(ss);  // Loop: read blocks of lines separated by a new line
    }
    std::vector<unsigned int>             listOfNumbers {};
    std::vector<std::vector<std::string>> listOfBoards {};
};

TEST_F(BingoPlayerTest, InputWorks)
{
    std::vector<unsigned int> expectedListOfNumbers {7,  4, 9,  5,  11, 17, 23, 2,  0, 14, 21, 24, 10, 16,
                                                     13, 6, 15, 25, 12, 22, 18, 20, 8, 19, 3,  26, 1};
    EXPECT_EQ(listOfNumbers, expectedListOfNumbers);

    std::vector<std::vector<std::string>> expectedListOfBoards {{
                                                                    "22 13 17 11  0",
                                                                    " 8  2 23  4 24",
                                                                    "21  9 14 16  7",
                                                                    " 6 10  3 18  5",
                                                                    " 1 12 20 15 19",
                                                                },
                                                                {
                                                                    " 3 15  0  2 22",
                                                                    " 9 18 13 17  5",
                                                                    "19  8  7 25 23",
                                                                    "20 11 10 24  4",
                                                                    "14 21 16 12  6",
                                                                },
                                                                {
                                                                    "14 21 17 24  4",
                                                                    "10 16 15  9 19",
                                                                    "18  8 23 26 20",
                                                                    "22 11 13  6  5",
                                                                    "2  0 12  3  7",
                                                                }};
    EXPECT_EQ(listOfBoards, expectedListOfBoards);
}

TEST_F(BingoPlayerTest, ParseBoards)
{
    std::vector<std::vector<std::vector<unsigned int>>> parsedBoards;
    for(const auto& boardStr : listOfBoards)
    {
        std::vector<std::vector<unsigned int>> board;
        for(const auto& line : boardStr)
        {
            std::stringstream ss(line);
            auto              lineVec = utils::parsing::parseSpaceSeparatedLine<unsigned int>(ss);
            board.push_back(lineVec);
        }
        parsedBoards.push_back(board);
    }

    std::vector<std::vector<std::vector<unsigned int>>> expectedParsedBoards {{
                                                                                  {22, 13, 17, 11, 0},
                                                                                  {8, 2, 23, 4, 24},
                                                                                  {21, 9, 14, 16, 7},
                                                                                  {6, 10, 3, 18, 5},
                                                                                  {1, 12, 20, 15, 19},
                                                                              },
                                                                              {
                                                                                  {3, 15, 0, 2, 22},
                                                                                  {9, 18, 13, 17, 5},
                                                                                  {19, 8, 7, 25, 23},
                                                                                  {20, 11, 10, 24, 4},
                                                                                  {14, 21, 16, 12, 6},
                                                                              },
                                                                              {
                                                                                  {14, 21, 17, 24, 4},
                                                                                  {10, 16, 15, 9, 19},
                                                                                  {18, 8, 23, 26, 20},
                                                                                  {22, 11, 13, 6, 5},
                                                                                  {2, 0, 12, 3, 7},
                                                                              }};
    EXPECT_EQ(parsedBoards, expectedParsedBoards);
}
// {
//     std::vector<day_3::PowerConsumptionCalculator::ReportLine> expectedResult {
//         {false, false, true, false, false},
//         {true, true, true, true, false},
//         {true, false, true, true, false},
//         {true, false, true, true, true},
//         {true, false, true, false, true},
//         {false, true, true, true, true},
//         {false, false, true, true, true},
//         {true, true, true, false, false},
//         {true, false, false, false, false},
//         {true, true, false, false, true},
//         {false, false, false, true, false},
//         {false, true, false, true, false},
//     };

//     EXPECT_EQ(calc.getFullReport(), expectedResult);
// }

// TEST_F(BingoPlayerTest, GetMostCommonBitTest)
// {
//     EXPECT_TRUE(calc.getMostCommonBit(calc.getFullReport(), 0));
//     EXPECT_FALSE(calc.getMostCommonBit(calc.getFullReport(), 1));
//     EXPECT_TRUE(calc.getMostCommonBit(calc.getFullReport(), 2));
//     EXPECT_TRUE(calc.getMostCommonBit(calc.getFullReport(), 3));
//     EXPECT_FALSE(calc.getMostCommonBit(calc.getFullReport(), 4));
// }

// TEST_F(BingoPlayerTest, GetLeastCommonBitTest)
// {
//     EXPECT_FALSE(calc.getLeastCommonBit(calc.getFullReport(), 0));
//     EXPECT_TRUE(calc.getLeastCommonBit(calc.getFullReport(), 1));
//     EXPECT_FALSE(calc.getLeastCommonBit(calc.getFullReport(), 2));
//     EXPECT_FALSE(calc.getLeastCommonBit(calc.getFullReport(), 3));
//     EXPECT_TRUE(calc.getLeastCommonBit(calc.getFullReport(), 4));
// }

// TEST_F(BingoPlayerTest, CalcGammaRate)
// {
//     EXPECT_EQ(calc.calculateGammaRate(), 22);
// }

// TEST_F(BingoPlayerTest, CalcEpsilonRate)
// {
//     EXPECT_EQ(calc.calculateEpsilonRate(), 9);
// }

// TEST_F(BingoPlayerTest, CalcFinalAnswer)
// {
//     EXPECT_EQ(calc.calculatePowerConsumption(), 198);
// }

// TEST_F(BingoPlayerTest, CalcOxygenGeneratorRating)
// {
//     EXPECT_EQ(calc.calculateOxygenGeneratorRating(), 23);
// }

// TEST_F(BingoPlayerTest, CalcCo2ScrubberRating)
// {
//     EXPECT_EQ(calc.calculateCo2ScrubberRating(), 10);
// }

// TEST_F(BingoPlayerTest, CalcLifeSupportRating)
// {
//     EXPECT_EQ(calc.calculateLifeSupportRating(), 230);
// }