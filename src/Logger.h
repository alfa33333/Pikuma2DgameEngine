#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
    public:
        static void Log(std::string& message);
        static void Err(std::string& message);
};

#endif