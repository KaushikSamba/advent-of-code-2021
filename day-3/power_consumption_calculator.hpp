#include <array>
#include <vector>

namespace day_3
{
constexpr std::size_t NUM_BITS = 5;

class PowerConsumptionCalculator
{
public:
    using ReportLine = std::array<bool, NUM_BITS>;
    PowerConsumptionCalculator();
    PowerConsumptionCalculator(std::vector<std::string> const& input);
    bool                    getMostCommonBit(std::size_t bit_position) const;
    bool                    getLeastCommonBit(std::size_t bit_position) const;
    std::vector<ReportLine> getFullReport() const;

    int calculateGammaRate() const;

private:
    std::tuple<std::size_t, std::size_t> getBitCount(std::size_t bit_position) const;

    std::vector<ReportLine> m_report;
};
}  // namespace day_3