#include "utils/filehandler.hpp"

long countIncreases(std::vector<long> inputVector)
{
    int numIncreases = 0;
    for(std::size_t i = 1; i < inputVector.size(); i++)
    {
        const auto val = inputVector[i];
        if(val > inputVector[i - 1])
        {
            numIncreases++;
        }
    }
    return numIncreases;
}

int main(int argc, char** argv)
{
    std::cout << "Filename: " << argv[1] << '\n';
    auto inputVector = utils::FileHandler {argv[1]}.getInputVector<long>();

    // auto result = countIncreases(inputVector);
    // Part 2 solution
    std::vector<long> slidingWindowVector;
    for(std::size_t i = 2; i < inputVector.size(); i++)
    {
        slidingWindowVector.push_back(inputVector[i] + inputVector[i - 1] + inputVector[i - 2]);
    }
    auto result = countIncreases(slidingWindowVector);
    // End part 2 solution

    std::cout << "Final answer: " << result << '\n';
    return 0;
}