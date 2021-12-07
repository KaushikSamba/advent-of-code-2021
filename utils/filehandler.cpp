#include "filehandler.hpp"

namespace utils
{

FileHandler::FileHandler(std::string filepath)
{
    stream.open(filepath);
    if(!stream)
    {
        std::cerr << "Unable to open file.\n";
        exit(1);
    }
}

FileHandler::~FileHandler()
{
    stream.close();
}

}  // namespace utils