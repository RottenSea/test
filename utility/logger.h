#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class Logger
{
public:
    enum level
    {
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    Logger(level level, const std::string &message) : logFile("log.log", std::ios::app)
    {
        log(level, message);
    }

    ~Logger()
    {
        if (logFile.is_open())
        {
            logFile.close();
        }
    }

private:
    std::ofstream logFile;
    std::string getCurrentTime()
    {
        std::time_t now = std::time(nullptr);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        return std::string(buffer);
    }

    void log(level level, const std::string &message)
    {
        if (logFile.is_open())
        {
            logFile << getCurrentTime() << " [" << levelToString(level) << "] " << message << std::endl;
        }
    }

    std::string levelToString(level level)
    {
        switch (level)
        {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARN:
            return "WARN";
        case ERROR:
            return "ERROR";
        case FATAL:
            return "FATAL";
        default:
            return "UNKNOWN";
        }
    }
};




