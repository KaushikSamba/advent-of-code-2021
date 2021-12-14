#include <array>
#include <queue>
#include <vector>

// Things that need to be fixed:
// -
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


class BingoPlayer
{
public:
    BingoPlayer();

    void parseInputFile(std::istream& stream);
    void play();
    uint getPart1Answer() const;
    uint getPart2Answer() const;

    std::vector<uint>                           getNumberList() const;
    std::vector<std::vector<std::vector<uint>>> getParsedBoards() const;

    uint getNextNumber();

    static uint calculateAnswer(BOARD const& board, uint lastNumber);

    static uint getSumOfUnmarkedNumbers(BOARD const& board);
    static bool findAndMarkNumberOnBoard(BOARD& board, uint number);  // True if bingo, false otherwise.
    static void markNumberOnBoard(BOARD& board, std::size_t row, std::size_t col);
    static std::tuple<bool, std::size_t, std::size_t> findNumberInBoard(BOARD& board, uint number);
    static bool                                       checkBingoRow(BOARD& board, std::size_t row);
    static bool                                       checkBingoColumn(BOARD& board, std::size_t col);

    std::vector<BOARD> m_boards;

    bool checkAllBoardsCompleted() const;  // True if all boards are completed, false otherwise.

private:
    void createInternalBoardRepresentation();

    std::vector<uint>                           m_number_list;
    std::vector<std::vector<std::vector<uint>>> m_parsed_boards;
    std::queue<uint>                            m_number_queue;
    uint                                        m_part_1_answer;
    uint                                        m_part_2_answer;
};
}  // namespace solution