#include <iostream>
#include <ctime>

#include "logger.h"

int main()
{
    std::time_t now = std::time(nullptr);

    std::tm* local_now = std::localtime(&now);

    char buffer[32];

    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local_now);

    std::cout << "当前时间: " << buffer << std::endl;

    return 0;
}

std::string filepath = "";

void LogToFile() {

};

void Logger::Log(Level level, const std::string *message)
{
    LevelToString(level);
}
