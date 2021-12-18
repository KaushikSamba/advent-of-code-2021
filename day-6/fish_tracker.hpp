#include <deque>
#include <istream>
#include <vector>

namespace solution
{

static const long long NEW_FISH_TIME   = 8;
static const long long FISH_RESET_TIME = 6;

class FishTracker
{
public:
    FishTracker();

    void parseInput(std::vector<long long> const& initialFishTimers);

    void      simulateDays(std::size_t days);
    long long getNumberOfFish() const;


    std::deque<long long> getQueue() const;

private:
    void                  simulateOneDay();
    std::deque<long long> m_fishQueue;
};

}  // namespace solution