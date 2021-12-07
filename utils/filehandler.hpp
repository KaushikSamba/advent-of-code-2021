// This file holds a file handler object that abstracts away the opening and
// closing of the file stream.

// Interesting C++ things I've done:
//    - Needed to overload the >> operator so that the file is entirely handled
//    by the RAII object and not by the user.
//    - Template function for the operator overload so that it is compatible
//    with any data type that is to be read.
//    - Include guards. These protect against re-inclusion of the header file.
//    - Custom function that handles CSV files.

#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <fstream>
#include <iostream>
#include <vector>

namespace utils
{

class FileHandler
{
public:
    explicit FileHandler(std::string);
    ~FileHandler();
    template<typename T> std::istream&  operator>>(T&);
    template<typename T> void           comma_separated_file(std::vector<T>&);
    template<typename T> std::vector<T> getInputVector();

private:
    std::ifstream stream;
};

template<typename T> std::istream& FileHandler::operator>>(T& data)
{
    return stream >> data;
}

template<typename T> void FileHandler::comma_separated_file(std::vector<T>& array)
{
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
}

template<typename T> std::vector<T> FileHandler::getInputVector()
{
    std::vector<T> outputVector;
    T              value;
    while(stream >> value)
    {
        outputVector.push_back(value);
    }
    return outputVector;
}

}  // namespace utils
#endif  // FILEHANDLER_HPP
