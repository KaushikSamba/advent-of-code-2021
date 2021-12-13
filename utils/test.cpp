#include <sstream>
#include "input_parser.hpp"
#include <gtest/gtest.h>

TEST(InputParserTest, CommaSeparatedLineNoCommaAtEnd)
{
    std::string       input("7,4,9,5,11,17");
    std::stringstream ss {input};
    std::vector<int>  expectedResult {7, 4, 9, 5, 11, 17};

    EXPECT_EQ(utils::parsing::parseCommaSeparatedLine<int>(ss), expectedResult);
}

TEST(InputParserTest, NewLineSeparatedInputs)
{
    std::string                           input = R""""(
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
    std::stringstream                     ss {input};
    std::vector<std::vector<std::string>> expectedResult {{
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

    EXPECT_EQ(utils::parsing::parseNewLineSeparatedInputs(ss), expectedResult);
}

TEST(InputParserTest, SpaceSeparatedString)
{
    std::string               input {"22 13 17 11  0"};
    std::stringstream         ss(input);
    std::vector<unsigned int> expectedResult {22, 13, 17, 11, 0};
    EXPECT_EQ(utils::parsing::parseSpaceSeparatedLine<unsigned int>(ss), expectedResult);
}
