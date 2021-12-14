#include <array>
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

    std::vector<uint>                           getNumberList() const;
    std::vector<std::vector<std::vector<uint>>> getParsedBoards() const;

private:
    std::vector<uint>                           m_number_list;
    std::vector<std::vector<std::vector<uint>>> m_parsed_boards;
    std::vector<BOARD>                          m_boards;
};
}  // namespace solution