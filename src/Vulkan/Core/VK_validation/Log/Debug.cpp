#include "Debug.h"

#include <Utility/Namespace.h>
#include <iostream>
#include <string>


namespace vk::validation::log{

//Constructor / Destructor
Debug::Debug(){}
Debug::~Debug(){}

//Main function
void Debug::print_message(std::string message){
  //---------------------------

  this->print_header(message);
  //this->print_severity(message);
  this->print_message_ID(message);

  //---------------------------
}

//Subfunction
void Debug::print_header(std::string message){
  //---------------------------

  //Isolate message
  std::cerr << "--------------------------" << std::endl;

  //---------------------------
}
void Debug::print_severity(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity){
  std::string severity = "";
  //---------------------------

  //Determine severity
  switch (message_severity){
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:{
      severity = "VERBOSE";
      break;
    }
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:{
      severity = "INFO";
      break;
    }
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:{
      severity = "WARNING";
      break;
    }
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:{
      severity = "ERROR";
      break;
    }
    default:{
      severity = "UNKNOWN";
      break;
    }
  }

  //Print it
  std::cout << "Validation [\033[1;33m" << severity << "\033[0m]" << std::endl;

  //---------------------------
}
void Debug::print_message_ID(std::string message){
  //---------------------------

  //Message ID title
  size_t msg_start = message.find("MessageID = ");
  size_t msg_end = message.find(" |", msg_start);
  std::string msg_title = message.substr(msg_start, msg_end - msg_start);

  //Message ID body
  std::string msg_body = message.substr(msg_end + 3);
  //size_t link_start = msg_body.find_last_of("https://") - 2;
  //msg_body = msg_body.substr(0, link_start) + ".";

  std::cerr << "\033[1;33m" << msg_title << "\033[0m" << std::endl;
  std::cerr << msg_body << std::endl;

  //---------------------------
}

}
