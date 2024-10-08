#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <memory>


namespace utl::log{

class Logger{
public:
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

  // Get the single instance of Logger
  static Logger& getInstance(const std::string& logFilePath) {
    static Logger instance(logFilePath); // Guaranteed to be destroyed
    return instance; // Instantiated on first use
  }

public:
  // Log levels
  enum class LogLevel {
    Info,
    Warning,
    Error
  };

  //Main function
  void log(LogLevel level, const std::string& message);

private:
  // Private constructor
  Logger(const std::string& logFilePath);
  ~Logger();

  std::string formatMessage(LogLevel level, const std::string& message);

private:
  std::ofstream file;
  std::mutex mutex;
};

}
