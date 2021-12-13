#include <istream>
#include <vector>

namespace utils
{
namespace parsing
{
template<typename T> std::vector<T> parseCommaSeparatedLine(std::istream& stream)
{
    std::vector<T> array;
    // For files with commas, the >> operator casts commas to integers and
    // generally makes a mess of the whole thing. It's better to have a custom
    // function that handles this case and pushes the relevant data into a
    // vector.
    T    data;
    char ch;
    while(stream >> data >> ch && ch == ',')
    {
        array.push_back(data);
    }
    // The last value does not have a comma after it, and so it is not read in
    // by the above loop.
    stream >> data;
    array.push_back(data);
    return array;
}

template<typename T> std::vector<T> parseSpaceSeparatedLine(std::istream& stream)
{
    std::vector<T> outputVector;
    T              value;
    while(stream >> value)
    {
        outputVector.push_back(value);
    }
    return outputVector;
}

std::vector<std::vector<std::string>> parseNewLineSeparatedInputs(std::istream& stream);

}  // namespace parsing
}  // namespace utils