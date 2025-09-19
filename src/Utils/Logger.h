#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>

class Logger {
public:
    static void init(const std::string& filename);
    static void log(const std::string& message);
    static void shutdown();

private:
    static std::ofstream logFile;
};

#endif //LOGGER_H
