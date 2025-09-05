#include "Logger.h"

std::ofstream Logger::logFile;

void Logger::init(const std::string& filename) {
    logFile.open(filename, std::ios::out | std::ios::app);
}

void Logger::log(const std::string& message) {
    if (logFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);

        std::tm now_tm{};
#if defined(_WIN32)
        localtime_s(&now_tm, &now_c);
#else
        localtime_r(&now_c, &now_tm);
#endif

        std::ostringstream oss;
        oss << "[" << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << "] ";
        oss << message;

        logFile << oss.str() << std::endl;
    }
}

void Logger::shutdown() {
    if (logFile.is_open()) {
        logFile.close();
    }
}