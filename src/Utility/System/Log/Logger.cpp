#include "Logger.h"


namespace utl::log{

//Constructor / Destructor
Logger::Logger(const std::string& path){
  //---------------------------
/*
  this->file.open(path, std::ios::app);

  if(!file.is_open()){
    throw std::runtime_error("Could not open log file");
  }
*/
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
void Logger::log(utl::log::Level level, const std::string& message) {
  //---------------------------
/*
  std::lock_guard<std::mutex> lock(mutex); // thread-safe logging
  std::string log = format_message(level, message);
  file << log << std::endl; // Log to file
*/
  //---------------------------
}
std::string Logger::format_message(utl::log::Level level, const std::string& message) {
  //---------------------------
/*
  std::string level_str;
  switch (level) {
    case utl::log::INFO:    level_str = "INFO"; break;
    case utl::log::WARNING: level_str = "WARNING"; break;
    case utl::log::ERROR:   level_str = "ERROR"; break;
  }

  //---------------------------
  return "[" + level_str + "] " + message;*/
  return "";
}

}
