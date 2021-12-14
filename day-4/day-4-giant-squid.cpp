#include "bingo_player.hpp"
#include "utils/filehandler.hpp"

int main(int argc, char** argv)
{
    if(!argv[1])
    {
        throw std::runtime_error("No filename supplied!");
    }

    std::string filename = argv[1];
    std::cout << "Filename: " << filename << '\n';

    solution::BingoPlayer solver;

    // Limit scope of file stream
    {
        std::ifstream stream {filename};
        solver.parseInputFile(stream);
    }

    auto result = solver.play();

    std::cout << "Part 1 Answer = " << result << '\n';
    return 0;
}