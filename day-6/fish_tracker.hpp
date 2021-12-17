#include <istream>
#include <map>
#include <vector>

namespace solution
{


struct Lanternfish
{
    static const uint NEW_FISH_TIME   = 8;
    static const uint FISH_RESET_TIME = 6;

    Lanternfish(uint initialTimer = NEW_FISH_TIME);
    bool operator==(Lanternfish const& other) const;

    uint internalTimer;
};

class FishTracker
{
public:
    FishTracker();

    void parseInput(std::vector<uint> const& initialFishTimers);


    std::vector<Lanternfish> m_fish;

    void        simulateDays(std::size_t days);
    std::size_t getNumberOfFish() const;

    // void                     registerAllLines();
    // uint calculateFinalAnswer() const;
    // uint getPart2Answer() const;
private:
    void simulateOneDay();
    // uint m_part_2_answer;
};


}  // namespace solution