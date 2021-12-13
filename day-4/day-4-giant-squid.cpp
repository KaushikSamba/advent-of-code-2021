#include "bingo_player.hpp"
#include "utils/filehandler.hpp"

int main(int argc, char** argv)
{
    std::cout << "Filename: " << argv[1] << '\n';
    auto inputVector = utils::FileHandler {argv[1]}.getInputVector<std::string>();

    solution::BingoPlayer solver;

    // std::cout << "Power consumption: " << solver.calculatePowerConsumption() << '\n'
    //   << "Life support rating: " << solver.calculateLifeSupportRating() << '\n';
    return 0;
}