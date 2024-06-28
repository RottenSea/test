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

    std::string *message;
    std::string *folderpath = "logs";
    static void Log(Level level, const std::string *message);

    std::string GetCurrentTime()
    {
        std::time_t now = std::time(nullptr);

        std::tm *local_now = std::localtime(&now);

        char buffer[32];

        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local_now);

        return buffer;
    }

    static void LogToFile(std::string message, std::string folderpath)
    {
        if (std::filesystem::create_directory(folderpath))
        {
            std::cout << "folder created: " << folderpath << std::endl;
        }
        else
        {
            std::cerr << "Folder creation failure or already exists: " << folderpath << std::endl;
        }

        std::ofstream ofs("logs/log.log", std::ios::app);
        if (!ofs.is_open())
        {
            std::cout << "无法打开日志文件" << std::endl;
            return;
        }
        ofs << message << std::endl;
        ofs.close();
    };

    void Logger::Log(Level level, const std::string *message)
    {
        LevelToString(level);

        std::string filename = GetCurrentTime() + ".log";

        std::string filepath = "logs/" + filename;

        LogToFile(*message, *message);
    }

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