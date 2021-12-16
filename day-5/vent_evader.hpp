#include <istream>
#include <map>
#include <vector>

namespace solution
{

struct Point
{
    uint x;
    uint y;
    bool operator==(const Point& other) const
    {
        return (x == other.x) && (y == other.y);
    }
};

struct Line
{
    Point startPoint;
    Point endPoint;

    bool operator==(const Line& other) const;

    bool               isCommonX() const;
    bool               isCommonY() const;
    std::vector<Point> getPointsInStraightLine() const;
};

namespace helpers
{
float getLineSlope(Line const& line);
}  // namespace helpers

class VentEvader
{
public:
    VentEvader();

    void parseInputLines(std::vector<std::string> const& inputLines);

    uint calculateFinalAnswer() const;

    uint getPart2Answer() const;

    std::vector<Line>                     m_lines;
    std::map<std::pair<uint, uint>, uint> m_map;
    void                                  registerLinePointsInMap(Line const& line);
    void                                  registerAllLines();

private:
    uint m_part_2_answer;
};
}  // namespace solution