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

    static void Initialize()
    {
        CreateFolder();
        SetFilename();
    }

    static void Log(const Level &level, const std::string &message)
    {
        LogToFile(LevelToString(level), message);
    }

    static std::string GetCurrentDate()
    {
        std::time_t now = std::time(nullptr);
        std::tm *local_now = std::localtime(&now);
        char buffer[16];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", local_now);
        return buffer;
    }

    static std::string GetCurrentTime()
    {
        std::time_t now = std::time(nullptr);
        std::tm *local_now = std::localtime(&now);
        char buffer[16];
        std::strftime(buffer, sizeof(buffer), "%H-%M-%S", local_now);
        return buffer;
    }

    static void CreateFolder()
    {
        if (!std::filesystem::exists(folderpath))
        {
            if (!std::filesystem::create_directories(folderpath))
            {
                std::cerr << "Folder creation failure or already exists: " << folderpath << std::endl;
            }
        }
    }

    static void SetFilename()
    {
        filename = folderpath + "/" + GetCurrentDate() + "_" + GetCurrentTime() + ".log";
    }

    static void LogToFile(const std::string &level, const std::string &message)
    {
        std::ofstream ofs(filename, std::ios::app);
        if (!ofs.is_open())
        {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }
        std::string time = GetCurrentTime();
        ofs << "[" << level << "] " << "[" << time << "] " << message << std::endl;
        ofs.close();
    }

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

std::string Logger::folderpath = "logs";
std::string Logger::filename;