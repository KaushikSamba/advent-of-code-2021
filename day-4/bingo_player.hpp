#include <array>
#include <queue>
#include <vector>

namespace solution
{

struct BoardElement
{
    uint number;
    bool marked = false;
};

static constexpr std::size_t BOARD_SIZE = 5;
using BOARD_ROW                         = std::array<BoardElement, BOARD_SIZE>;
// using BOARD                             = std::array<BOARD_ROW, BOARD_SIZE>;

struct BOARD
{
    BOARD_ROW& at(std::size_t n)
    {
        return board.at(n);
    }

    const BOARD_ROW* begin() const
    {
        return board.begin();
    }

    const BOARD_ROW* end() const
    {
        return board.end();
    }

    bool                              completed = false;
    std::array<BOARD_ROW, BOARD_SIZE> board;
};

namespace helpers
{
uint calculateAnswer(BOARD const& board, uint lastNumber);
uint getSumOfUnmarkedNumbers(BOARD const& board);
bool findAndMarkNumberOnBoard(BOARD& board, uint number);  // True if bingo, false otherwise.
void markNumberOnBoard(BOARD& board, std::size_t row, std::size_t col);
std::tuple<bool, std::size_t, std::size_t> findNumberInBoard(BOARD& board, uint number);
bool                                       checkBingoRow(BOARD& board, std::size_t row);
bool                                       checkBingoColumn(BOARD& board, std::size_t col);
}  // namespace helpers

class BingoPlayer
{
public:
    BingoPlayer();

    void parseInputFile(std::istream& stream);
    void play();
    uint getPart1Answer() const;
    uint getPart2Answer() const;

    // Stuff that is public only for testing. BAD practice.
    std::vector<uint>                           getNumberList() const;
    std::vector<std::vector<std::vector<uint>>> getParsedBoards() const;
    uint                                        getNextNumber();
    std::vector<BOARD>                          m_boards;


private:
    bool checkAllBoardsCompleted() const;  // True if all boards are completed, false otherwise.
    void createInternalBoardRepresentation();

    std::vector<uint>                           m_number_list;
    std::vector<std::vector<std::vector<uint>>> m_parsed_boards;
    std::queue<uint>                            m_number_queue;
    uint                                        m_part_1_answer;
    uint                                        m_part_2_answer;
};
}  // namespace solution