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
    using Report     = std::vector<ReportLine>;
    using Rate       = std::vector<bool>;
    PowerConsumptionCalculator();
    PowerConsumptionCalculator(std::vector<std::string> const& input);
    static bool getMostCommonBit(Report const& report, std::size_t bit_position);
    static bool getLeastCommonBit(Report const& report, std::size_t bit_position);
    Report      getFullReport() const;

    Rate          calculateRate(std::function<bool(std::size_t)> func) const;
    unsigned long calculateGammaRate() const;
    unsigned long calculateEpsilonRate() const;
    unsigned long calculatePowerConsumption() const;
    unsigned long calculateOxygenGeneratorRating() const;

    static unsigned long convertBinaryToDecimal(
        std::vector<bool>
            binaryValue);  // Binary value must be arranged in order from least significant digit to most significant.

    Report filterReport(Report const& input, bool value, std::size_t bit_position) const;

private:
    static std::tuple<std::size_t, std::size_t> getBitCount(Report const& report, std::size_t bit_position);
    std::size_t                                 NUM_BITS;
    Report                                      m_report;
};
}  // namespace day_3