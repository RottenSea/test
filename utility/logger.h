#pragma once

#include <iostream>
#include <fstream>

class Logger
{
public:
    enum level
    {
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    Logger(level log_level) : m_log_rank(log_level){};

    ~Logger();

    static std::ostream &start(level log_level, const int32_t line, const std::string &function);

    friend void initLogger(const std::string &info_log_filename,
                           const std::string &warn_log_filename,
                           const std::string &error_log_filename);

private:
    static std::ostream &getStream(level log_level);

    static std::ofstream m_info_log_file;
    static std::ofstream m_warn_log_file;
    static std::ofstream m_error_log_file;
    level m_log_rank;
};
