#include <array>
#include <vector>

namespace solution
{

struct BoardElement
{
    uint8_t number;
    bool    marked = false;
};

static constexpr std::size_t BOARD_SIZE = 5;
using BOARD_ROW                         = std::array<BoardElement, BOARD_SIZE>;
using BOARD                             = std::array<BOARD_ROW, BOARD_SIZE>;

class BingoPlayer
{
public:
    BingoPlayer();

    void setSelectedNumbers(std::vector<uint8_t> const& selectedNumbers);

private:
    std::vector<uint8_t> m_number_list;
    std::vector<BOARD>   m_boards;
};
}  // namespace solution