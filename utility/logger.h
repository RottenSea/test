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
    static std::string filename;

    Logger()
    {
        CreateFolder();
    };

    void Log(const Level &level, const std::string &message)
    {
        Logger::LogToFile(LevelToString(level), message);
    }

    static std::string GetCurrentTime()
    {
        std::time_t now = std::time(nullptr);
        std::tm *local_now = std::localtime(&now);
        char buffer[32];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local_now);
        return buffer;
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
            std::cout << "Folder path: " << folderpath << std::endl;
            void SetFilename();
            std::cout << "Log file: " << filename << std::endl;
        }
    };

    static void LogToFile(const std::string &level, const std::string &message)
    {
        std::ofstream ofs(filename, std::ios::app);
        std::string time = GetCurrentTime();
        std::cout << "[" << level << "] " << "[" << time << "] " << message << filename << std::endl;

        if (!ofs.is_open())
        {
            std::cerr << "Failed to open file: " << Logger::filename << std::endl;
            return;
        }
        ofs << "[" << level << "] " << "[" << time << "] " << message << std::endl;
        ofs.close();
    };

    static void SetFilename()
    {
        Logger::filename = folderpath + "/" + GetCurrentTime() + ".log";
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

