#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem>
#define LOG_LEVEL 0

const std::string Logger::folderpath = "logs";
const std::string Logger::filename = GetCurrentTime() + ".log";

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

    static std::string GetCurrentTime()
    {
        std::time_t now = std::time(nullptr);

        std::tm *local_now = std::localtime(&now);

        char buffer[32];

        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local_now);

        return buffer;
    }

    Logger()
    {
        CreateFolder();
    };

    void Log(Level level, const std::string *message)
    {
        Logger::LogToFile(GetCurrentTime(), LevelToString(level), *message);
    }

    void CreateFolder()
    {
        if (std::filesystem::create_directory(folderpath))
        {
            std::cout << "folder created: " << folderpath << std::endl;
        }
        else
        {
            std::cerr << "Folder creation failure or already exists: " << folderpath << std::endl;
        }
    }

    void LogToFile(std::string time, std::string level, std::string message)
    {
        std::ofstream ofs(Logger::filename, std::ios::app);
        if (!ofs.is_open())
        {
            std::cerr << "Failed to open file" << Logger::folderpath << std::endl;
            return;
        }
        ofs << "[" << level << "] " << "[" << time << "]" << message << std::endl;
        ofs.close();
    };

private:
    static const std::string folderpath;
    static const std::string filename;

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
