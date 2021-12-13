#include "power_consumption_calculator.hpp"
#include "utils/filehandler.hpp"

int main(int argc, char** argv)
{
    std::cout << "Filename: " << argv[1] << '\n';
    auto inputVector = utils::FileHandler {argv[1]}.getInputVector<std::string>();

    day_3::PowerConsumptionCalculator solver(inputVector);

    std::cout << "Power consumption: " << solver.calculatePowerConsumption() << '\n'
              << "Life support rating: " << solver.calculateLifeSupportRating() << '\n';
    return 0;
}