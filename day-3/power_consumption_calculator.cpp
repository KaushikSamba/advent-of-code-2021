#include "power_consumption_calculator.hpp"
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
        for(std::size_t i = 0; i < NUM_BITS; i++)
        {

            auto letter = num[i];
            if(letter == '0')
            {
                line[i] = false;
            }
            else if(letter == '1')
            {
                line[i] = true;
            }
            else
            {
                throw std::runtime_error("Unknown letter received! Letter: " + letter);
            }
        }
        m_report.push_back(line);
    }
}

std::vector<PowerConsumptionCalculator::ReportLine> PowerConsumptionCalculator::getFullReport() const
{
    return m_report;
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
    std::cout << "In column " << bit_position << " , num of zeros = " << zero_count << ", num of ones = " << one_count
              << std::endl;
    return {zero_count, one_count};
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

int PowerConsumptionCalculator::calculateGammaRate() const {}
}  // namespace day_3