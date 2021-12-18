#include <fstream>
#include <iostream>
#include "fish_tracker.hpp"
#include "utils/input_parser.hpp"

int main(int argc, char** argv)
{
    if(!argv[1])
    {
        throw std::runtime_error("No filename supplied!");
    }

    std::string filename = argv[1];
    std::cout << "Filename: " << filename << '\n';

    solution::FishTracker solver;


    // Limit scope of file stream
    {
        std::ifstream          stream {filename};
        std::vector<long long> inputLines = utils::parsing::parseCommaSeparatedLine<long long>(stream);
        solver.parseInput(inputLines);
    }

    solver.simulateDays(256);

    std::cout << "Answer = " << solver.getNumberOfFish() << '\n';
    return 0;
}