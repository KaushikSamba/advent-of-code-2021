#include "utils/filehandler.hpp"
enum class Command
{
    FORWARD,
    UP,
    DOWN
};

std::ostream& operator<<(std::ostream& stream, Command const& c)
{
    std::string command;
    if(c == Command::FORWARD)
    {
        command = "forward";
    }
    else if(c == Command::DOWN)
    {
        command = "down";
    }
    else if(c == Command::UP)
    {
        command = "up";
    }
    else
    {
        throw std::runtime_error("Unknown command received!");
    }
    stream << command;
    return stream;
}

struct Instruction
{
    Command command;
    int     units;
};

std::istream& operator>>(std::istream& stream, Instruction& I)
{
    std::string command;
    stream >> command >> I.units;
    if(!command.empty())
    {
        if(command == "forward")
        {
            I.command = Command::FORWARD;
        }
        else if(command == "up")
        {
            I.command = Command::UP;
        }
        else if(command == "down")
        {
            I.command = Command::DOWN;
        }
        else
        {
            throw std::runtime_error("Unknown command (" + command + ") received!");
        }
    }
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

    int hPos  = 0;
    int depth = 0;
    int aim   = 0;
    for(const auto& instr : inputVector)
    {
        switch(instr.command)
        {
        case Command::FORWARD:
            hPos += instr.units;
            depth += aim * instr.units;
            break;
        case Command::UP:
            aim -= instr.units;
            break;
        case Command::DOWN:
            aim += instr.units;
            break;
        }
    }

    const auto result = hPos * depth;
    std::cout << "Final answer: " << result << '\n';
    return 0;
}