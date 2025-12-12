#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>


class Logger {
    std::ofstream logFile;

public:
    Logger(const std::string& filename = "log.txt") : logFile(filename,std::ios::app) {}

    void log(const std::string& message) {
        auto now = std::chrono::system_clock::now();

        auto time_t = std::chrono::system_clock::to_time_t(now);

        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        std::ostringstream oss;

        oss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        oss << "." << std::setfill('0') << std::setw(3) << ms.count();

        logFile << "[" << oss.str() << "] " << message << std::endl;

        logFile.flush();
    }
};

#endif