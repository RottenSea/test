#include "logger.h"

int main()
{
    Logger::Initialize();
    LOG_INFO("message");
    LOG_ERROR("error");
    return 0;
}