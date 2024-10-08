#include "Logger.h"


namespace utl::log{

//Constructor / Destructor
Logger::Logger(const std::string& path){
  //---------------------------

  this->file.open(path, std::ios::app);

  if(!file.is_open()){
    throw std::runtime_error("Could not open log file");
  }

  //---------------------------
}
Logger::~Logger(){
  //---------------------------

  if(file.is_open()){
    file.close();
  }

  //---------------------------
}

//Main function
void Logger::log(LogLevel level, const std::string& message) {
  //---------------------------

  std::lock_guard<std::mutex> lock(mutex); // thread-safe logging
  std::string logMessage = formatMessage(level, message);
  std::cout << logMessage << std::endl; // Log to console
  file << logMessage << std::endl; // Log to file

  //---------------------------
}
std::string Logger::formatMessage(LogLevel level, const std::string& message) {
  //---------------------------

  std::string levelStr;
  switch (level) {
    case LogLevel::Info:    levelStr = "INFO"; break;
    case LogLevel::Warning: levelStr = "WARNING"; break;
    case LogLevel::Error:   levelStr = "ERROR"; break;
  }

  //---------------------------
  return "[" + levelStr + "] " + message;
}

}
