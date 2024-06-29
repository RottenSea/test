#include "logger.h"

int main()
{
    std::cout << "Hello, world!" << std::endl;

    logger.Log(Logger::Level::Info, "test message");
}
