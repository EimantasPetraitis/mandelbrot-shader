#include "ReadFile.h"

std::string ReadFile(const std::string& path)
{

    std::ifstream fileStream(path);
    std::ostringstream stringStream;
    stringStream << fileStream.rdbuf();

    return stringStream.str();

}