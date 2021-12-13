#include <array>
#include <bitset>
#include <functional>
#include <vector>

namespace day_3
{
class PowerConsumptionCalculator
{
public:
    using ReportLine = std::vector<bool>;
    using Rate       = std::vector<bool>;
    PowerConsumptionCalculator();
    PowerConsumptionCalculator(std::vector<std::string> const& input);
    bool                    getMostCommonBit(std::size_t bit_position) const;
    bool                    getLeastCommonBit(std::size_t bit_position) const;
    std::vector<ReportLine> getFullReport() const;

    Rate          calculateRate(std::function<bool(std::size_t)> func) const;
    unsigned long calculateGammaRate() const;
    unsigned long calculateEpsilonRate() const;
    unsigned long calculateFinalAnswer() const;

    static unsigned long convertBinaryToDecimal(
        Rate binaryValue);  // Binary value must be arranged in order from least significant digit to most significant.

private:
    std::tuple<std::size_t, std::size_t> getBitCount(std::size_t bit_position) const;
    std::size_t                          NUM_BITS;
    std::vector<ReportLine>              m_report;
};
}  // namespace day_3