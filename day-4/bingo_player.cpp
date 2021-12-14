#include "bingo_player.hpp"
#include <iostream>
#include <sstream>
#include <tuple>
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

    m_number_queue = std::queue<uint>(std::deque<uint>(m_number_list.begin(), m_number_list.end()));
    createInternalBoardRepresentation();
}

std::vector<uint> BingoPlayer::getNumberList() const
{
    return m_number_list;
}

std::vector<std::vector<std::vector<uint>>> BingoPlayer::getParsedBoards() const
{
    return m_parsed_boards;
}

uint BingoPlayer::getNextNumber()
{
    auto number = m_number_queue.front();
    m_number_queue.pop();
    return number;
}

uint BingoPlayer::play()
{
    while(true)
    {
        auto        num = getNextNumber();
        std::size_t i   = 0;
        for(auto& board : m_boards)
        {
            i++;
            if(findAndMarkNumberOnBoard(board, num))
            {
                // This board has scored a bingo!
                return calculatePart1Answer(board, num);
            }
        }
    }
}

uint BingoPlayer::calculatePart1Answer(BOARD const& board, uint lastNumber)
{
    return (getSumOfUnmarkedNumbers(board) * lastNumber);
}

uint BingoPlayer::getSumOfUnmarkedNumbers(BOARD const& board)
{
    uint sum = 0;
    for(const auto& row : board)
    {
        for(const auto& elem : row)
        {
            if(!elem.marked)
            {
                sum += elem.number;
            }
        }
    }
    return sum;
}

bool BingoPlayer::findAndMarkNumberOnBoard(BOARD& board, uint number)
{
    bool        success;
    std::size_t row, col;
    std::tie(success, row, col) = findNumberInBoard(board, number);
    if(success)
    {
        markNumberOnBoard(board, row, col);
        return (checkBingoRow(board, row) or checkBingoColumn(board, col));
    }
    return false;
}

void BingoPlayer::markNumberOnBoard(BOARD& board, std::size_t row, std::size_t col)
{
    board.at(row).at(col).marked = true;
}


void BingoPlayer::createInternalBoardRepresentation()
{
    for(const auto& b : m_parsed_boards)
    {
        solution::BOARD board;
        if(b.size() != solution::BOARD_SIZE)
        {
            throw std::runtime_error("Parsed board has more rows than the board size!");
        }
        for(std::size_t i = 0; i < solution::BOARD_SIZE; i++)
        {
            const auto& row = b.at(i);
            if(row.size() != solution::BOARD_SIZE)
            {
                throw std::runtime_error("Parsed board row has more columns than the board size!");
            }
            for(std::size_t j = 0; j < solution::BOARD_SIZE; j++)
            {
                auto& boardElement  = board.at(i).at(j);
                boardElement.number = row.at(j);
                boardElement.marked = false;
            }
        }
        m_boards.push_back(board);
    }
}

std::tuple<bool, std::size_t, std::size_t> BingoPlayer::findNumberInBoard(BOARD& board, uint number)
{
    for(std::size_t i = 0; i < BOARD_SIZE; i++)
    {
        for(std::size_t j = 0; j < BOARD_SIZE; j++)
        {
            if(board.at(i).at(j).number == number)
            {
                return {true, i, j};
            }
        }
    }
    return {false, 0, 0};
}

bool BingoPlayer::checkBingoRow(BOARD& board, std::size_t row)
{
    for(const auto& elem : board.at(row))
    {
        if(!elem.marked)
        {
            return false;
        }
    }
    return true;
}

bool BingoPlayer::checkBingoColumn(BOARD& board, std::size_t col)
{
    for(std::size_t row = 0; row < BOARD_SIZE; row++)
    {
        if(!board.at(row).at(col).marked)
        {
            return false;
        }
    }
    return true;
}

}  // namespace solution