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
using BOARD                             = std::array<BOARD_ROW, BOARD_SIZE>;

class BingoPlayer
{
public:
    BingoPlayer();

    void setSelectedNumbers(std::vector<uint> const& selectedNumbers);

    void parseInputFile(std::istream& stream);
    uint play();

    std::vector<uint>                           getNumberList() const;
    std::vector<std::vector<std::vector<uint>>> getParsedBoards() const;

    uint getNextNumber();

    uint calculatePart1Answer(BOARD const& board, uint lastNumber);

    static uint getSumOfUnmarkedNumbers(BOARD const& board);
    static bool findAndMarkNumberOnBoard(BOARD& board, uint number);  // True if bingo, false otherwise.
    static void markNumberOnBoard(BOARD& board, std::size_t row, std::size_t col);
    static std::tuple<bool, std::size_t, std::size_t> findNumberInBoard(BOARD& board, uint number);
    static bool                                       checkBingoRow(BOARD& board, std::size_t row);
    static bool                                       checkBingoColumn(BOARD& board, std::size_t col);

    std::vector<BOARD> m_boards;

private:
    void createInternalBoardRepresentation();

    std::vector<uint>                           m_number_list;
    std::vector<std::vector<std::vector<uint>>> m_parsed_boards;
    std::queue<uint>                            m_number_queue;
};
}  // namespace solution