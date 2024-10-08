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
  static Logger& get_instance(const std::string& path) {
    static Logger instance(path); // Guaranteed to be destroyed
    return instance; // Instantiated on first use
  }

public:
  //Main function
  void log(utl::log::Level level, const std::string& message);

private:
  // Private constructor
  Logger(const std::string& path);
  ~Logger();

  std::string format_message(utl::log::Level level, const std::string& message);

private:
  std::ofstream file;
  std::mutex mutex;
};

}
