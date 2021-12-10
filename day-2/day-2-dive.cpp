#include "utils/filehandler.hpp"

struct Instruction
{
    std::string command;
    int         units;
};

std::istream& operator>>(std::istream& stream, Instruction& I)
{
    stream >> I.command >> I.units;
    return stream;
}

std::ostream& operator<<(std::ostream& stream, Instruction const& I)
{
    stream << I.command << ' ' << I.units << '\n';
    return stream;
}

int main(int argc, char** argv)
{
    if(!argv[1])
    {
        throw std::runtime_error("No filename supplied!");
    }

    std::string filename = argv[1];
    std::cout << "Filename: " << filename << '\n';
    auto inputVector = utils::FileHandler {filename}.getInputVector<Instruction>();

    for(const auto& value : inputVector)
    {
        std::cout << value;
    }

    // std::cout << "Final answer: " << result << '\n';
    return 0;
}