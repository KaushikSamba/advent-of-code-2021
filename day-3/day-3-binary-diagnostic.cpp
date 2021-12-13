#include "utils/filehandler.hpp"

int main(int argc, char** argv)
{
    std::cout << "Filename: " << argv[1] << '\n';
    auto inputVector = utils::FileHandler {argv[1]}.getInputVector<long>();

    int result = 0;
    std::cout << "Final answer: " << result << '\n';
    return 0;
}