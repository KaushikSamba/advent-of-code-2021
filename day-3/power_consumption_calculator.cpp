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

std::tuple<std::size_t, std::size_t> PowerConsumptionCalculator::getBitCount(std::size_t bit_position) const
{
    std::size_t zero_count = 0;
    std::size_t one_count  = 0;
    for(const auto& line : m_report)
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

unsigned long PowerConsumptionCalculator::convertBinaryToDecimal(Rate binaryValue)
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

bool PowerConsumptionCalculator::getMostCommonBit(std::size_t bit_position) const
{
    auto [zero_count, one_count] = getBitCount(bit_position);
    return (one_count > zero_count);
}

bool PowerConsumptionCalculator::getLeastCommonBit(std::size_t bit_position) const
{
    auto [zero_count, one_count] = getBitCount(bit_position);
    return (one_count < zero_count);
}

unsigned long PowerConsumptionCalculator::calculateGammaRate() const
{
    Rate gammaRate = calculateRate([this](std::size_t i) { return getMostCommonBit(i); });
    return convertBinaryToDecimal(gammaRate);
}

unsigned long PowerConsumptionCalculator::calculateEpsilonRate() const
{
    Rate epsilonRate = calculateRate([this](std::size_t i) { return getLeastCommonBit(i); });
    return convertBinaryToDecimal(epsilonRate);
}

unsigned long PowerConsumptionCalculator::calculatePowerConsumption() const
{
    return (calculateGammaRate() * calculateEpsilonRate());
}
}  // namespace day_3