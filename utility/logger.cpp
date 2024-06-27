#include <cstdlib>
#include <ctime>
#include <string>

#include "logger.h"

const std::string filename = "log.log";
std::string message = "";

void Logger::Log(Logger::Level level, const char * message)
{
    std::time_t now = std::time(nullptr);
    std::tm *local_time = std::localtime(&now);
    char time_buffer[100];
    std::strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", local_time);

    std::ofstream log_file(filename, std::ios::app);
    log_file << time_buffer << " " << message << std::endl;
    log_file.close();
}
