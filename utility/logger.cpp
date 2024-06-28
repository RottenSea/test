#include "logger.h"

std::string message = "Hello, world!";

void LogToFile()
{
    std::string folderpath = "logs";
    if (std::filesystem::create_directory(folderpath))
    {
        std::cout << "文件夹创建成功：" << folderpath << std::endl;
    }
    else
    {
        std::cerr << "文件夹创建失败或文件夹已存在：" << folderpath << std::endl;
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

std::string GetCurrentTime()
{
    std::time_t now = std::time(nullptr);

    std::tm *local_now = std::localtime(&now);

    char buffer[32];

    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local_now);

    std::cout << "当前时间: " << buffer << std::endl;

    return buffer;
}

void Logger::Log(Level level, const std::string *message)
{
    LevelToString(level);

    std::string filename = GetCurrentTime() + ".log";

    std::string filepath = "logs/" + filename;

    LogToFile();
}

int main()
{
    std::cout << "Hello, world!" << std::endl;
    LogToFile();
}
