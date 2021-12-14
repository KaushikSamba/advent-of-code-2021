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

        solver.parseInputFile(ss);
    }
    solution::BingoPlayer     solver;
    std::vector<unsigned int> expectedListOfNumbers {7,  4, 9,  5,  11, 17, 23, 2,  0, 14, 21, 24, 10, 16,
                                                     13, 6, 15, 25, 12, 22, 18, 20, 8, 19, 3,  26, 1};
};

TEST_F(BingoPlayerTest, InputWorks)
{
    EXPECT_EQ(solver.getNumberList(), expectedListOfNumbers);

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
    EXPECT_EQ(solver.getParsedBoards(), expectedParsedBoards);
}

TEST_F(BingoPlayerTest, PopNumbers)
{
    for(const auto& num : expectedListOfNumbers)
    {
        EXPECT_EQ(solver.getNextNumber(), num);
    }
}

TEST_F(BingoPlayerTest, FindNumberInBoard)
{
    // for(auto& board : solver.m_boards)
    // {
    //     EXPECT_EQ(solver.findNumberInBoard(board, 7), );
    //     EXPECT_NE(solver.findNumberInBoard(board, 4), nullptr);
    //     EXPECT_NE(solver.findNumberInBoard(board, 5), nullptr);
    //     EXPECT_NE(solver.findNumberInBoard(board, 9), nullptr);
    //     EXPECT_NE(solver.findNumberInBoard(board, 11), nullptr);
    //     EXPECT_EQ(solver.findNumberInBoard(board, 27), nullptr);
    // }
}

TEST_F(BingoPlayerTest, MarkNumberInBoard)
{
    // for(auto& board : solver.m_boards)
    // {
    //     EXPECT_TRUE(solver.markNumberOnBoard(board, 7));
    //     EXPECT_TRUE(solver.markNumberOnBoard(board, 4));
    //     EXPECT_TRUE(solver.markNumberOnBoard(board, 5));
    //     EXPECT_TRUE(solver.markNumberOnBoard(board, 9));
    //     EXPECT_TRUE(solver.markNumberOnBoard(board, 11));
    //     EXPECT_FALSE(solver.markNumberOnBoard(board, 27));
    // }

    {
        auto& board = solver.m_boards.at(0);
        solver.findAndMarkNumberOnBoard(board, 7);
        EXPECT_TRUE(board.at(2).at(4).marked);
        solver.findAndMarkNumberOnBoard(board, 4);
        EXPECT_TRUE(board.at(1).at(3).marked);
        solver.findAndMarkNumberOnBoard(board, 5);
        EXPECT_TRUE(board.at(3).at(4).marked);
    }


    // EXPECT_TRUE(solver.m_boards.at(1).at(2).at(2).marked);  // 7
    // EXPECT_TRUE(solver.m_boards.at(2).at(4).at(4).marked);  // 7
    // EXPECT_TRUE(solver.m_boards.at(1).at(3).at(4).marked);  // 4
    // EXPECT_TRUE(solver.m_boards.at(2).at(0).at(4).marked);  // 4
    // EXPECT_TRUE(solver.m_boards.at(1).at(1).at(4).marked);  // 5
    // EXPECT_TRUE(solver.m_boards.at(2).at(3).at(4).marked);  // 5
}

TEST_F(BingoPlayerTest, CheckBingoRow)
{
    auto& board = solver.m_boards.at(2);
    EXPECT_FALSE(solver.findAndMarkNumberOnBoard(board, 14));
    EXPECT_FALSE(solver.findAndMarkNumberOnBoard(board, 21));
    EXPECT_FALSE(solver.findAndMarkNumberOnBoard(board, 17));
    EXPECT_FALSE(solver.findAndMarkNumberOnBoard(board, 24));
    EXPECT_TRUE(solver.findAndMarkNumberOnBoard(board, 4));
}

TEST_F(BingoPlayerTest, CheckBingoCol)
{
    auto& board = solver.m_boards.at(2);
    EXPECT_FALSE(solver.findAndMarkNumberOnBoard(board, 14));
    EXPECT_FALSE(solver.findAndMarkNumberOnBoard(board, 10));
    EXPECT_FALSE(solver.findAndMarkNumberOnBoard(board, 18));
    EXPECT_FALSE(solver.findAndMarkNumberOnBoard(board, 22));
    EXPECT_TRUE(solver.findAndMarkNumberOnBoard(board, 2));
}

TEST_F(BingoPlayerTest, PlayBingo)
{
    solver.play();
    EXPECT_EQ(solver.getPart1Answer(), 4512);
    EXPECT_EQ(solver.getPart2Answer(), 1924);
}
