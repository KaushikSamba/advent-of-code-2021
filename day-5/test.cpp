#include "utils/input_parser.hpp"
#include "vent_evader.hpp"
#include <gtest/gtest.h>

TEST(SlopeTest, PositiveSlope)
{
    using solution::Line;
    using solution::Point;
    Line line {Point {1, 1}, Point {3, 3}};
    EXPECT_FLOAT_EQ(solution::helpers::getLineSlope(line), 1);
}

TEST(SlopeTest, NegativeSlope)
{
    using solution::Line;
    using solution::Point;
    Line line {Point {9, 7}, Point {7, 9}};
    EXPECT_FLOAT_EQ(solution::helpers::getLineSlope(line), -1);
}

TEST(SlopeTest, NegativeSlope2)
{
    using solution::Line;
    using solution::Point;
    Line line {Point {8, 0}, Point {0, 8}};
    EXPECT_FLOAT_EQ(solution::helpers::getLineSlope(line), -1);
}
class VentEvaderTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        std::string inputFile = R""""(0,9 -> 5,9
8,0 -> 0,8
9,4 -> 3,4
2,2 -> 2,1
7,0 -> 7,4
6,4 -> 2,0
0,9 -> 2,9
3,4 -> 1,4
0,0 -> 8,8
5,5 -> 8,2
)"""";

        std::stringstream        ss(inputFile);
        std::vector<std::string> inputLines = utils::parsing::parseNewLineTerminatedLinesAsStrings(ss);
        solver.parseInputLines(inputLines);
    }
    solution::VentEvader solver;
};

TEST_F(VentEvaderTest, InputWorks)
{
    using solution::Line;
    using solution::Point;

    std::vector<Line> expectedLines {
        Line {Point {0, 9}, Point {5, 9}},
        Line {Point {8, 0}, Point {0, 8}},
        Line {Point {9, 4}, Point {3, 4}},
        Line {Point {2, 2}, Point {2, 1}},
        Line {Point {7, 0}, Point {7, 4}},
        Line {Point {6, 4}, Point {2, 0}},
        Line {Point {0, 9}, Point {2, 9}},
        Line {Point {3, 4}, Point {1, 4}},
        Line {Point {0, 0}, Point {8, 8}},
        Line {Point {5, 5}, Point {8, 2}},
    };
    EXPECT_EQ(solver.m_lines, expectedLines);
}

TEST_F(VentEvaderTest, RegisterYLine)
{
    using solution::Line;
    using solution::Point;
    Line line {Point {0, 9}, Point {5, 9}};

    solver.registerLinePointsInMap(line);

    EXPECT_EQ(solver.m_map.at({0, 9}), 1);
    EXPECT_EQ(solver.m_map.at({1, 9}), 1);
    EXPECT_EQ(solver.m_map.at({2, 9}), 1);
    EXPECT_EQ(solver.m_map.at({3, 9}), 1);
    EXPECT_EQ(solver.m_map.at({4, 9}), 1);
    EXPECT_EQ(solver.m_map.at({5, 9}), 1);
}

TEST_F(VentEvaderTest, RegisterXLine)
{
    using solution::Line;
    using solution::Point;
    Line line {Point {7, 0}, Point {7, 4}};

    solver.registerLinePointsInMap(line);

    EXPECT_EQ(solver.m_map.at({7, 0}), 1);
    EXPECT_EQ(solver.m_map.at({7, 1}), 1);
    EXPECT_EQ(solver.m_map.at({7, 2}), 1);
    EXPECT_EQ(solver.m_map.at({7, 3}), 1);
    EXPECT_EQ(solver.m_map.at({7, 4}), 1);
}


TEST_F(VentEvaderTest, RegisterDiagonalLine1)
{
    using solution::Line;
    using solution::Point;
    Line line {Point {1, 1}, Point {3, 3}};

    solver.registerLinePointsInMap(line);

    EXPECT_EQ(solver.m_map.at({1, 1}), 1);
    EXPECT_EQ(solver.m_map.at({2, 2}), 1);
    EXPECT_EQ(solver.m_map.at({3, 3}), 1);
}

TEST_F(VentEvaderTest, RegisterDiagonalLine2)
{
    using solution::Line;
    using solution::Point;
    Line line {Point {9, 7}, Point {7, 9}};

    solver.registerLinePointsInMap(line);

    EXPECT_EQ(solver.m_map.at({9, 7}), 1);
    EXPECT_EQ(solver.m_map.at({8, 8}), 1);
    EXPECT_EQ(solver.m_map.at({7, 9}), 1);
}


TEST_F(VentEvaderTest, RegisterDiagonalLine3)
{
    using solution::Line;
    using solution::Point;
    Line line {Point {8, 0}, Point {0, 8}};

    solver.registerLinePointsInMap(line);

    EXPECT_EQ(solver.m_map.at({8, 0}), 1);
    EXPECT_EQ(solver.m_map.at({7, 1}), 1);
    EXPECT_EQ(solver.m_map.at({6, 2}), 1);
    EXPECT_EQ(solver.m_map.at({5, 3}), 1);
    EXPECT_EQ(solver.m_map.at({4, 4}), 1);
    EXPECT_EQ(solver.m_map.at({3, 5}), 1);
    EXPECT_EQ(solver.m_map.at({2, 6}), 1);
    EXPECT_EQ(solver.m_map.at({1, 7}), 1);
    EXPECT_EQ(solver.m_map.at({0, 8}), 1);
}


TEST_F(VentEvaderTest, RegisterDiagonalLine4)
{
    using solution::Line;
    using solution::Point;
    Line line {Point {6, 4}, Point {2, 0}};

    solver.registerLinePointsInMap(line);

    EXPECT_EQ(solver.m_map.at({6, 4}), 1);
    EXPECT_EQ(solver.m_map.at({5, 3}), 1);
    EXPECT_EQ(solver.m_map.at({4, 2}), 1);
    EXPECT_EQ(solver.m_map.at({3, 1}), 1);
    EXPECT_EQ(solver.m_map.at({2, 0}), 1);
}

TEST_F(VentEvaderTest, RegisterDiagonalLine5)
{
    using solution::Line;
    using solution::Point;
    Line line {Point {5, 5}, Point {8, 2}};

    solver.registerLinePointsInMap(line);

    EXPECT_EQ(solver.m_map.at({5, 5}), 1);
    EXPECT_EQ(solver.m_map.at({6, 4}), 1);
    EXPECT_EQ(solver.m_map.at({7, 3}), 1);
    EXPECT_EQ(solver.m_map.at({8, 2}), 1);
}


TEST_F(VentEvaderTest, RegisterAllLines)
{
    solver.registerAllLines();


    std::map<std::pair<uint, uint>, uint> map {
        {{0, 0}, 1}, {{2, 0}, 1}, {{7, 0}, 1}, {{8, 0}, 1}, {{1, 1}, 1}, {{2, 1}, 1}, {{3, 1}, 1}, {{7, 1}, 2},
        {{2, 2}, 2}, {{4, 2}, 1}, {{6, 2}, 1}, {{7, 2}, 1}, {{8, 2}, 1}, {{3, 3}, 1}, {{5, 3}, 2}, {{7, 3}, 2},
        {{1, 4}, 1}, {{2, 4}, 1}, {{3, 4}, 2}, {{4, 4}, 3}, {{5, 4}, 1}, {{6, 4}, 3}, {{7, 4}, 2}, {{8, 4}, 1},
        {{9, 4}, 1}, {{3, 5}, 1}, {{5, 5}, 2}, {{2, 6}, 1}, {{6, 6}, 1}, {{1, 7}, 1}, {{7, 7}, 1}, {{0, 8}, 1},
        {{8, 8}, 1}, {{0, 9}, 2}, {{1, 9}, 2}, {{2, 9}, 2}, {{3, 9}, 1}, {{4, 9}, 1}, {{5, 9}, 1},
    };


    for(const auto& [key, value] : map)
    {
        uint val;
        EXPECT_NO_THROW(val = solver.m_map.at(key));
        EXPECT_EQ(map.at(key), val);
    }

    EXPECT_EQ(solver.calculateFinalAnswer(), 12);
}