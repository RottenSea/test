#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem>
#define LOG_LEVEL 0

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
    };

    static void Log(Level level, const std::string *message);

private:
    static std::string LevelToString(Level level)
    {
        switch (level)
        {
        case Level::Debug:
            return "Debug";
        case Level::Info:
            return "Info";
        case Level::Warning:
            return "Warning";
        case Level::Error:
            return "Error";
        case Level::Fatal:
            return "Fatal";
        default:
            return "Unknown";
        };
    };
};