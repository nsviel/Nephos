#include "Debug.h"

#include <Utility/Namespace.h>
#include <iostream>
#include <string>


namespace vk::validation::log{

//Main function
void Debug::print_message(std::string message){
  //---------------------------

  this->print_header(message);
  this->print_message_ID(message);

  //---------------------------
}

//Subfunction
void Debug::print_header(std::string message){
  //---------------------------

  // Split the message into individual objects
  size_t pose_obj_start = message.find("|");
  if (pose_obj_start == std::string::npos) {
    return; // Exit the function if the substring is not found
  }

  std::string validation_error = message.substr(0, pose_obj_start);

  std::cerr << "--------------------------" << std::endl;
  std::cerr << "[" << "\033[1;32mVL\033[0m] " << validation_error << std::endl;

  //---------------------------
}
void Debug::print_severity(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity){
  std::string severity = "";
  //---------------------------

  //Determine severity
  switch (message_severity){
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:{
      severity = "verbose";
      break;
    }
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:{
      severity = "info";
      break;
    }
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:{
      severity = "warning";
      break;
    }
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:{
      severity = "error";
      break;
    }
    default:{
      severity = "unknown";
      break;
    }
  }

  //Print it
  std::cout << "Severity: [\033[1;33m" << severity << "\033[0m]" << std::endl;

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
