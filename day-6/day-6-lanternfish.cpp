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
        std::ifstream     stream {filename};
        std::vector<uint> inputLines = utils::parsing::parseCommaSeparatedLine<uint>(stream);
        solver.parseInput(inputLines);
    }

    solver.simulateDays(80);

    std::cout << "Answer = " << solver.getNumberOfFish() << '\n';
    return 0;
}