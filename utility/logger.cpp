#include "logger.h"

int main()
{
    Logger logger;
    logger.Log(Logger::Info, "This is a test log message.");
    return 0;
}