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

        std::stringstream ss(inputFile);
        std::vector<uint> inputLines = utils::parsing::parseCommaSeparatedLine<uint>(ss);
        EXPECT_EQ(inputLines, expectedInput);

        solver.parseInput(inputLines);
    }
    std::vector<uint>     expectedInput {3, 4, 3, 1, 2};
    solution::FishTracker solver;
};

TEST_F(FishTrackerTest, FishCreated)
{
    for(std::size_t i = 0; i < expectedInput.size(); i++)
    {
        EXPECT_EQ(solver.m_fish.at(i), solution::Lanternfish {expectedInput.at(i)});
    }
}


TEST_F(FishTrackerTest, SimulateOneDay)
{
    solver.simulateDays(1);
    std::vector<uint> fishLives {2, 3, 2, 0, 1};
    for(std::size_t i = 0; i < expectedInput.size(); i++)
    {
        EXPECT_EQ(solver.m_fish.at(i).internalTimer, fishLives.at(i));
    }
}

TEST_F(FishTrackerTest, SimulateTwoDays)
{
    solver.simulateDays(2);
    std::vector<uint> fishLives {1, 2, 1, 6, 0, 8};
    for(std::size_t i = 0; i < expectedInput.size(); i++)
    {
        EXPECT_EQ(solver.m_fish.at(i).internalTimer, fishLives.at(i));
    }
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
