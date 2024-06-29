#include "logger.h"

int main()
{
    std::cout << "Hello, world!" << std::endl;
    Logger logger;

    logger.Log(Logger::Info, "test message");
}
