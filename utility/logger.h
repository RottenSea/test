#pragma once

#include <iostream>








class Logger
{
    
    private:



    public:
    enum Level
    {
        Debug,
        Info,
        Warning,
        Error,
        Fatal
    };
    static void Log(Level level, const char* message);
    
};







