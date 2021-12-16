#include "input_parser.hpp"

namespace utils
{
namespace parsing
{
std::vector<std::vector<std::string>> parseNewLineSeparatedInputs(std::istream& stream)
{
    std::string                           line;
    std::vector<std::string>              input;
    std::vector<std::vector<std::string>> inputNewLineSeparated;
    while(std::getline(stream, line, '\n'))
    {
        if(line.empty())
        {
            // std::cout << "Encountered empty line!\n";
            if(!input.empty())
            {
                inputNewLineSeparated.push_back(input);
                input.clear();
            }
        }
        else
        {
            input.push_back(line);
            // std::cout << "Pushed line: " << line << '\n';
        }
    }
    if(!input.empty())  // If the last block does not have a trailing new line.
    {
        inputNewLineSeparated.push_back(input);
    }
    return inputNewLineSeparated;
}

std::vector<std::string> parseNewLineTerminatedLinesAsStrings(std::istream& stream)
{
    std::vector<std::string> parsedLines;
    std::string              line;
    while(std::getline(stream, line, '\n'))
    {
        if(!line.empty())
        {
            parsedLines.push_back(line);
        }
    }
    return parsedLines;
}

}  // namespace parsing
}  // namespace utils