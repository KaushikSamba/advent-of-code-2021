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

    auto result = countIncreases(inputVector);

    std::cout << "Final answer: " << result << '\n';
    return 0;
}