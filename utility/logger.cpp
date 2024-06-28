#include "logger.h"

std::string message = "Hello, world!";

int main()
{
    std::cout << "Hello, world!" << std::endl;
    Logger::LogToFile();
}

