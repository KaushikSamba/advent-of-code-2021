#include "bingo_player.hpp"
#include <sstream>
#include "utils/input_parser.hpp"

namespace solution
{
BingoPlayer::BingoPlayer() = default;

void BingoPlayer::parseInputFile(std::istream& stream)
{
    std::string line;
    // The first line is comma separated, gives the list of numbers:
    std::getline(stream, line, '\n');

    // Parse the list of numbers
    std::stringstream numberListStream {line};
    m_number_list = utils::parsing::parseCommaSeparatedLine<uint>(numberListStream);
    // Second line is empty
    std::getline(stream, line, '\n');

    // Parse the boards
    std::vector<std::vector<std::string>> listOfBoards =
        utils::parsing::parseNewLineSeparatedInputs(stream);  // Loop: read blocks of lines separated by a new line

    for(const auto& boardStr : listOfBoards)
    {
        std::vector<std::vector<uint>> board;
        for(const auto& line : boardStr)
        {
            std::stringstream stream(line);
            auto              lineVec = utils::parsing::parseSpaceSeparatedLine<uint>(stream);
            board.push_back(lineVec);
        }
        m_parsed_boards.push_back(board);
    }
}

std::vector<uint> BingoPlayer::getNumberList() const
{
    return m_number_list;
}

std::vector<std::vector<std::vector<uint>>> BingoPlayer::getParsedBoards() const
{
    return m_parsed_boards;
}


}  // namespace solution