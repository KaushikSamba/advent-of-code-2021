#include "fish_tracker.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>

namespace solution
{
Lanternfish::Lanternfish(uint initialTimer)
    : internalTimer(initialTimer)
{}

bool Lanternfish::operator==(Lanternfish const& other) const
{
    return internalTimer == other.internalTimer;
}

FishTracker::FishTracker() = default;

void FishTracker::parseInput(std::vector<uint> const& initialFishTimers)
{
    for(const auto& time : initialFishTimers)
    {
        m_fish.emplace_back(Lanternfish {time});
    }
}

void FishTracker::simulateOneDay()
{
    std::size_t numNewFish = 0;
    for(auto& fish : m_fish)
    {
        if(fish.internalTimer == 0)
        {
            // A new fish needs to be spawned:
            ++numNewFish;
            fish.internalTimer = Lanternfish::FISH_RESET_TIME;
        }
        else
        {
            --fish.internalTimer;
        }
    }
    while(numNewFish > 0)
    {
        m_fish.emplace_back(Lanternfish {Lanternfish::NEW_FISH_TIME});
        --numNewFish;
    }
}

void FishTracker::simulateDays(std::size_t days)
{
    for(std::size_t i = 0; i < days; i++)
    {
        simulateOneDay();
    }
}

std::size_t FishTracker::getNumberOfFish() const
{
    return m_fish.size();
}

}  // namespace solution