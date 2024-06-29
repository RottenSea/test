#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem>
#include <string>

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
    static const std::string filename;

    Logger()
    {
        CreateFolder();
    };

    static std::string GetCurrentTime()
    {
        std::time_t now = std::time(nullptr);
        std::tm *local_now = std::localtime(&now);
        char buffer[32];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local_now);
        return buffer;
    }

    void Log(const Level &level, const std::string &message)
    {
        Logger::LogToFile(Logger::GetCurrentTime(), LevelToString(level), message);
    }

    static void CreateFolder()
    {
        if (!std::filesystem::exists(folderpath))
        {
            std::cout << "Creating folder: " << folderpath << std::endl;
            if (std::filesystem::create_directories(folderpath))
            {
                std::cout << "Folder created: " << folderpath << std::endl;
            }
            else
            {
                std::cerr << "Folder creation failure or already exists: " << folderpath << std::endl;
            }
        }
    };

    void LogToFile(const std::string &time, const std::string &level, const std::string &message)
    {
        std::ofstream ofs(Logger::filename, std::ios::app);
        if (!ofs.is_open())
        {
            std::cerr << "Failed to open file: " << Logger::filename << std::endl;
            return;
        }
        ofs << "[" << level << "] " << "[" << time << "] " << message << std::endl;
        ofs.close();
    };

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
const std::string Logger::filename = Logger::folderpath + "/" + Logger::GetCurrentTime() + ".log";

