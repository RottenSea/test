#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem>
#include <string>

#define LOG_DEBUG(message) Logger::Log(Logger::Level::Debug, message)   
#define LOG_INFO(message) Logger::Log(Logger::Info, message);
#define LOG_WARNING(message) Logger::Log(Logger::Level::Warning, message)   
#define LOG_ERROR(message) Logger::Log(Logger::Level::Error, message)   
#define LOG_FATAL(message) Logger::Log(Logger::Level::Fatal, message)   

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

    static std::string folderpath;
    static std::string filename;
    static std::string message;

    static void Initialize();

    static void Log(const Level &level, const std::string message);

    static std::string GetCurrentDate();

    static std::string GetCurrentTime();

    static void CreateFolder();

    static void SetFilename();

    static void LogToFile(const std::string &level, const std::string &message);

private:
    static const std::string LevelToString(Level level)
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
        }
    }
};
