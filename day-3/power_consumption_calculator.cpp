#include "power_consumption_calculator.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <tuple>

namespace day_3
{
PowerConsumptionCalculator::PowerConsumptionCalculator() = default;
PowerConsumptionCalculator::PowerConsumptionCalculator(std::vector<std::string> const& input)
{
    for(const auto& num : input)
    {
        if(num.empty())
        {
            continue;
        }
        ReportLine line;
        for(std::size_t i = 0; i < num.length(); i++)
        {
            auto letter = num.at(i);
            if(letter == '0')
            {
                line.push_back(false);
            }
            else if(letter == '1')
            {
                line.push_back(true);
            }
            else
            {
                throw std::runtime_error("Unknown letter received! Letter: " + letter);
            }
        }
        m_report.push_back(line);
    }
    NUM_BITS = m_report.at(0).size();  // Number of bits in any given line.
}

std::vector<PowerConsumptionCalculator::ReportLine> PowerConsumptionCalculator::getFullReport() const
{
    return m_report;
}

PowerConsumptionCalculator::Rate PowerConsumptionCalculator::calculateRate(std::function<bool(std::size_t)> func) const
{
    Rate rate;
    for(std::size_t i = 0; i < NUM_BITS; i++)
    {
        rate.push_back(func(i));
    }

    std::reverse(rate.begin(), rate.end());  // The bitset indexing is from least significant bit to most significant.
                                             // The 0th bit value is the most signficant of the rate.

    return rate;
}

std::tuple<std::size_t, std::size_t> PowerConsumptionCalculator::getBitCount(Report const& report,
                                                                             std::size_t   bit_position)
{
    std::size_t zero_count = 0;
    std::size_t one_count  = 0;
    for(const auto& line : report)
    {
        if(line.at(bit_position))
        {
            one_count++;
        }
        else
        {
            zero_count++;
        }
    }
    return {zero_count, one_count};
}

unsigned long PowerConsumptionCalculator::convertBinaryToDecimal(std::vector<bool> binaryValue)
{
    unsigned long result = 0;
    for(std::size_t i = 0; i < binaryValue.size(); i++)
    {
        if(binaryValue[i])
        {
            result += std::pow(2, i);
        }
    }
    return result;
}

bool PowerConsumptionCalculator::getMostCommonBit(Report const& report, std::size_t bit_position)
{
    auto [zero_count, one_count] = getBitCount(report, bit_position);
    return (one_count >= zero_count);
}

bool PowerConsumptionCalculator::getLeastCommonBit(Report const& report, std::size_t bit_position)
{
    auto [zero_count, one_count] = getBitCount(report, bit_position);
    return (one_count < zero_count);
}

unsigned long PowerConsumptionCalculator::calculateGammaRate() const
{
    Rate gammaRate = calculateRate([this](std::size_t i) { return getMostCommonBit(m_report, i); });
    return convertBinaryToDecimal(gammaRate);
}

unsigned long PowerConsumptionCalculator::calculateEpsilonRate() const
{
    Rate epsilonRate = calculateRate([this](std::size_t i) { return getLeastCommonBit(m_report, i); });
    return convertBinaryToDecimal(epsilonRate);
}

unsigned long PowerConsumptionCalculator::calculatePowerConsumption() const
{
    return (calculateGammaRate() * calculateEpsilonRate());
}

unsigned long PowerConsumptionCalculator::calculateOxygenGeneratorRating() const
{
    Report selectedNumbers = getFullReport();
    for(std::size_t i = 0; (i < NUM_BITS) && (selectedNumbers.size() != 1); i++)
    {
        auto mostCommonBit = getMostCommonBit(selectedNumbers, i);
        std::cout << "Criterion for bit " << i << " : " << mostCommonBit << '\n';
        selectedNumbers = filterReport(selectedNumbers, mostCommonBit, i);
    }
    if(selectedNumbers.size() != 1)
    {
        throw std::runtime_error(
            "Something horrible has happened! Went through all the bits and found more than one candidate match!");
    }
    auto finalNumber = selectedNumbers.at(0);
    std::cout << "Final number is : \n";
    for(const auto& val : finalNumber)
    {
        std::cout << val << ' ';
    }
    std::cout << std::endl;
    std::reverse(finalNumber.begin(), finalNumber.end());
    return convertBinaryToDecimal(finalNumber);
}

PowerConsumptionCalculator::Report PowerConsumptionCalculator::filterReport(
    PowerConsumptionCalculator::Report const& input,
    bool                                      value,
    std::size_t                               bit_position) const
{
    Report filteredReport;
    for(const auto& line : input)
    {
        if(line.at(bit_position) == value)
        {
            filteredReport.push_back(line);
        }
    }
    return filteredReport;
}

}  // namespace day_3