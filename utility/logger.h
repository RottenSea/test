#pragma once

#include <iostream>
#include <fstream>

void initLogger(const std::string &info_log_filename,
                const std::string &warn_log_filename,
                const std::string &error_log_filename);

class Logger
{
    friend void initLogger(const std::string &info_log_filename,
                           const std::string &warn_log_filename,
                           const std::string &error_log_filename);

public:
    Logger(level log_rank) : m_log_rank(log_rank){};
    ~Logger();
    static std::ostream &start(level log_rank, const int32_t line, const std::string &function);

private:
    enum level
    {
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    static std::ostream &getStream(level log_rank);

    static std::ofstream m_info_log_file;
    static std::ofstream m_warn_log_file;
    static std::ofstream m_error_log_file;
    log_rank_t m_log_rank;

    static void initLogger(const std::string &info_log_filename,
                           const std::string &warn_log_filename,
                           const std::string &error_log_filename)
    {
    }
};