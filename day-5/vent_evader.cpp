#include "vent_evader.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>

namespace solution
{

bool Line::operator==(const Line& other) const
{
    return (startPoint == other.startPoint) && (endPoint == other.endPoint);
}

bool Line::isCommonX() const
{
    return (startPoint.x == endPoint.x);
}

bool Line::isCommonY() const
{
    return (startPoint.y == endPoint.y);
}

std::vector<Point> Line::getPointsInStraightLine() const
{
    std::vector<Point> points {};
    auto               minX = std::min(startPoint.x, endPoint.x);
    auto               maxX = std::max(startPoint.x, endPoint.x);
    auto               minY = std::min(startPoint.y, endPoint.y);
    auto               maxY = std::max(startPoint.y, endPoint.y);
    if(isCommonX())
    {
        auto xCoor = startPoint.x;
        for(auto i = minY; i <= maxY; i++)
        {
            points.push_back(Point {xCoor, i});
        }
    }
    else if(isCommonY())
    {
        auto yCoor = startPoint.y;
        for(auto i = minX; i <= maxX; i++)
        {
            points.push_back(Point {i, yCoor});
        }
    }
    else
    {
        float slope = helpers::getLineSlope(*this);
        if(slope > 0)
        {
            // Slope is positive; x and y increase together.
            auto i = minX;
            auto j = minY;
            while(i <= maxX)
            {
                points.push_back(Point {i, j});
                ++i;
                ++j;
            }
        }
        else
        {
            // Slope is negative; x and y behave oppositely.
            auto i = minX;
            auto j = maxY;
            while(i <= maxX)
            {
                // std::cout << "endpoint.x = " << endPoint.x << '\t';
                // std::cout << i << '\t' << j << '\t' << (i >= endPoint.x) << '\n';
                points.push_back(Point {(uint)i, (uint)j});
                ++i;
                --j;
            }
        }
    }
    return points;
}

namespace helpers
{
float getLineSlope(Line const& line)
{
    float slope = ((float)line.endPoint.y - line.startPoint.y) / ((float)line.endPoint.x - line.startPoint.x);
    return slope;
}

}  // namespace helpers

VentEvader::VentEvader() = default;

void checkCharAndThrow(char const& ch, char const& value)
{
    if(ch != value)
    {
        throw std::runtime_error("Char " + std::string {value} +
                                 " expected; this char was parsed: " + std::string {ch});
    }
}

void VentEvader::parseInputLines(std::vector<std::string> const& inputLines)
{
    for(const auto& inputLine : inputLines)
    {
        std::stringstream ss(inputLine);
        uint              x1, y1, x2, y2;
        char              ch;
        ss >> x1 >> ch;
        checkCharAndThrow(ch, ',');
        ss >> y1;
        Point startPoint {x1, y1};
        ss >> ch;
        checkCharAndThrow(ch, '-');
        ss >> ch;
        checkCharAndThrow(ch, '>');
        ss >> x2;
        ss >> ch;
        checkCharAndThrow(ch, ',');
        ss >> y2;
        Point endPoint {x2, y2};
        m_lines.emplace_back(Line {startPoint, endPoint});
    }
}

void VentEvader::registerLinePointsInMap(Line const& line)
{
    for(const auto& point : line.getPointsInStraightLine())
    {
        if(m_map.find({point.x, point.y}) != m_map.end())
        {
            auto& currentVal = m_map.at({point.x, point.y});
            currentVal++;
        }
        else
        {
            m_map.insert({{point.x, point.y}, 1});
        }
    }
}

void VentEvader::registerAllLines()
{
    for(const auto& line : m_lines)
    {
        registerLinePointsInMap(line);
    }
}

uint VentEvader::calculateFinalAnswer() const
{
    uint part1Answer =
        std::count_if(m_map.begin(), m_map.end(), [](std::pair<std::pair<uint, uint>, unsigned int> elem) {
            return elem.second >= 2;
        });

    return part1Answer;
}

}  // namespace solution