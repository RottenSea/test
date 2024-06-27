#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

class Logger
{
public:
    enum Level
    {
        Debug,
        Info,
        Warning,
        Error,
        Fatal
    } level;

    static void Log(Level level, const char *message);

    Logger(std::string &filename) : logFile(filename, std::ios::app)
    {
        openfile(filename.c_str());
    }

    void openfile(const char *filename)
    {
        logFile.open(filename, std::ios::app);
        if (!logFile.is_open())
        {
            std::cerr << "Failed to open log file: " << filename << std::endl;
        }
    }

    std::string getTimeStamp()
    {
        time_t now = time(0);
        char *dt = ctime(&now);
        return std::string(dt);
    }

    void close()
    {
        logFile.close();
    }

private:
    std::ofstream logFile;

    static std::string levelToString(Level level)
    {
        switch (level)
        {
        case Debug:
            return std::string("Debug");
        case Info:
            return std::string("Info");
        case Warning:
            return std::string("Warning");
        case Error:
            return std::string("Error");
        case Fatal:
            return std::string("Fatal");
        }
    }
};
