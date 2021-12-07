#include "filehandler.hpp"

namespace utils
{

FileHandler::FileHandler(std::string filepath)
{
    stream.open(filepath);
    if(!stream)
    {
        throw std::runtime_error("Unable to open file.");
    }
}

FileHandler::~FileHandler()
{
    stream.close();
}

}  // namespace utils