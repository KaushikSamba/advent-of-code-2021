#include <fstream>
#include <iostream>
#include "utils/input_parser.hpp"
#include "vent_evader.hpp"

int main(int argc, char** argv)
{
    if(!argv[1])
    {
        throw std::runtime_error("No filename supplied!");
    }

    std::string filename = argv[1];
    std::cout << "Filename: " << filename << '\n';

    solution::VentEvader solver;

    // Limit scope of file stream
    {
        std::ifstream            stream {filename};
        std::vector<std::string> inputLines = utils::parsing::parseNewLineTerminatedLinesAsStrings(stream);
        solver.parseInputLines(inputLines);
    }

    solver.registerAllLines();

    std::cout << "Answer = " << solver.calculateFinalAnswer() << '\n';
    // std::cout << "Part 2 Answer = " << solver.getPart2Answer() << '\n';
    return 0;
}