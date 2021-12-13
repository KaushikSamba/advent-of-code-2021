#include "power_consumption_calculator.hpp"
#include "utils/filehandler.hpp"

int main(int argc, char** argv)
{
    std::cout << "Filename: " << argv[1] << '\n';
    auto inputVector = utils::FileHandler {argv[1]}.getInputVector<std::string>();

    auto result = day_3::PowerConsumptionCalculator(inputVector).calculateFinalAnswer();
    std::cout << "Final answer: " << result << '\n';
    return 0;
}