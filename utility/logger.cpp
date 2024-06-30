#include "logger.h"

std::string Logger::folderpath = "logs";
std::string Logger::filename;

void Logger::Initialize()
{
    CreateFolder();
    SetFilename();
}

void Logger::Log(const Level &level, const std::string message)
{
    LogToFile(LevelToString(level), message);
    std::cout << "[" << LevelToString(level) << "] " << message << std::endl;
}

std::string Logger::GetCurrentDate()
{
    std::time_t now = std::time(nullptr);
    std::tm *local_now = std::localtime(&now);
    char buffer[16];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", local_now);
    return buffer;
}

std::string Logger::GetCurrentTime()
{
    std::time_t now = std::time(nullptr);
    std::tm *local_now = std::localtime(&now);
    char buffer[16];
    std::strftime(buffer, sizeof(buffer), "%H-%M-%S", local_now);
    return buffer;
}

void Logger::CreateFolder()
{
    if (!std::filesystem::exists(folderpath))
    {
        if (!std::filesystem::create_directories(folderpath))
        {
            std::cerr << "Folder creation failure or already exists: " << folderpath << std::endl;
        }
    }
}

void Logger::SetFilename()
{
    filename = folderpath + "/" + GetCurrentDate() + "_" + GetCurrentTime() + ".log";
}

void Logger::LogToFile(const std::string &level, const std::string &message)
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
