#include "fish_tracker.hpp"
#include <algorithm>
#include <numeric>
#include <sstream>

namespace solution
{

FishTracker::FishTracker() = default;

void FishTracker::parseInput(std::vector<long long> const& initialFishTimers)
{
    for(long long i = 0; i <= NEW_FISH_TIME; i++)
    {
        long long count = std::count_if(
            initialFishTimers.begin(), initialFishTimers.end(), [i](const long long& value) { return (value == i); });
        m_fishQueue.push_back(count);
    }
}

void FishTracker::simulateOneDay()
{
    auto numZeroFish = m_fishQueue.front();
    m_fishQueue.pop_front();
    m_fishQueue.push_back(numZeroFish);
    m_fishQueue.at(FISH_RESET_TIME) += numZeroFish;
}

void FishTracker::simulateDays(std::size_t days)
{
    for(std::size_t i = 0; i < days; i++)
    {
        simulateOneDay();
    }
}

long long FishTracker::getNumberOfFish() const
{
    return std::accumulate(m_fishQueue.begin(), m_fishQueue.end(), (long long)0);
}

std::deque<long long> FishTracker::getQueue() const
{
    return m_fishQueue;
}
}  // namespace solution