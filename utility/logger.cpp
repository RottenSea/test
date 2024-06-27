#include <cstdlib>
#include <ctime>

#include "logger.h"

std::ofstream Logger::m_error_log_file;
std::ofstream Logger::m_info_log_file;
std::ofstream Logger::m_warn_log_file;

void initLogger(const std::string &info_log_filename,
                const std::string &warn_log_filename,
                const std::string &error_log_filename)
{
    Logger::m_info_log_file.open(info_log_filename.c_str());
    Logger::m_warn_log_file.open(warn_log_filename.c_str());
    Logger::m_error_log_file.open(error_log_filename.c_str());
}

std::ostream &Logger::start(level log_level,
                            const int line,
                            const std::string &function)
{
    time_t tm;
    time(&tm);
    char time_string[128];
    time_t(&tm) = tm;
    return getStream(log_rank) << time_string
                               << "function (" << function << ")"
                               << "line " << line
                               << std::flush;
}

























