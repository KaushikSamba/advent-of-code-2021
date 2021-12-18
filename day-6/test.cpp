#include "fish_tracker.hpp"
#include "utils/input_parser.hpp"
#include <gtest/gtest.h>

class FishTrackerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        std::string inputFile = R""""(3,4,3,1,2
)"""";

        std::stringstream      ss(inputFile);
        std::vector<long long> inputLines = utils::parsing::parseCommaSeparatedLine<long long>(ss);
        EXPECT_EQ(inputLines, expectedInput);

        solver.parseInput(inputLines);
    }
    std::vector<long long> expectedInput {3, 4, 3, 1, 2};
    solution::FishTracker  solver;
};

TEST_F(FishTrackerTest, FishCreated)
{
    auto q = solver.getQueue();
    EXPECT_EQ(q.front(), 0);  // 0
    q.pop_front();
    EXPECT_EQ(q.front(), 1);  // 1
    q.pop_front();
    EXPECT_EQ(q.front(), 1);  // 2
    q.pop_front();
    EXPECT_EQ(q.front(), 2);  // 3
    q.pop_front();
    EXPECT_EQ(q.front(), 1);  // 4
    q.pop_front();
    EXPECT_EQ(q.front(), 0);  // 5
    q.pop_front();
    EXPECT_EQ(q.front(), 0);  // 6
    q.pop_front();
    EXPECT_EQ(q.front(), 0);  // 7
    q.pop_front();
    EXPECT_EQ(q.front(), 0);  // 8
    q.pop_front();
}


TEST_F(FishTrackerTest, SimulateOneDay)
{
    solver.simulateDays(1);
    auto q = solver.getQueue();
    EXPECT_EQ(q.front(), 1);  // 0
    q.pop_front();
    EXPECT_EQ(q.front(), 1);  // 1
    q.pop_front();
    EXPECT_EQ(q.front(), 2);  // 2
    q.pop_front();
    EXPECT_EQ(q.front(), 1);  // 3
    q.pop_front();
    EXPECT_EQ(q.front(), 0);  // 4
    q.pop_front();
    EXPECT_EQ(q.front(), 0);  // 5
    q.pop_front();
    EXPECT_EQ(q.front(), 0);  // 6
    q.pop_front();
    EXPECT_EQ(q.front(), 0);  // 7
    q.pop_front();
    EXPECT_EQ(q.front(), 0);  // 8
    q.pop_front();
}

TEST_F(FishTrackerTest, SimulateTwoDays)
{
    solver.simulateDays(2);
    auto q = solver.getQueue();
    EXPECT_EQ(q.front(), 1);  // 0
    q.pop_front();
    EXPECT_EQ(q.front(), 2);  // 1
    q.pop_front();
    EXPECT_EQ(q.front(), 1);  // 2
    q.pop_front();
    EXPECT_EQ(q.front(), 0);  // 3
    q.pop_front();
    EXPECT_EQ(q.front(), 0);  // 4
    q.pop_front();
    EXPECT_EQ(q.front(), 0);  // 5
    q.pop_front();
    EXPECT_EQ(q.front(), 1);  // 6
    q.pop_front();
    EXPECT_EQ(q.front(), 0);  // 7
    q.pop_front();
    EXPECT_EQ(q.front(), 1);  // 8
    q.pop_front();
}

TEST_F(FishTrackerTest, Simulate18Days)
{
    solver.simulateDays(18);
    EXPECT_EQ(solver.getNumberOfFish(), 26);
}

TEST_F(FishTrackerTest, Simulate80Days)
{
    solver.simulateDays(80);
    EXPECT_EQ(solver.getNumberOfFish(), 5934);
}

TEST_F(FishTrackerTest, Simulate256Days)
{
    solver.simulateDays(256);
    EXPECT_EQ(solver.getNumberOfFish(), 26984457539);
}
