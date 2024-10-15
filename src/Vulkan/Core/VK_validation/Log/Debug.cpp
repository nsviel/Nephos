#include "Debug.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <iostream>
#include <string>


namespace vk::validation::log{

//Constructor / Destructor
Debug::Debug(){}
Debug::~Debug(){}

//Main function
void Debug::print_message(vk::validation::Message& message){
  //---------------------------

  this->print_header(message);
  this->print_body(message);

  //---------------------------
}

//Subfunction
void Debug::print_header(vk::validation::Message& message){
  //---------------------------

  //Isolate message
  std::cerr << "--------------------------" << std::endl;
  std::cout << "Validation [\033[1;31m" << message.severity << "\033[0m]" << std::endl;

  //Message ID
  size_t msg_start = message.text.find("MessageID = ");
  if(msg_start == std::string::npos) return;
  size_t msg_end = message.text.find(" |", msg_start);
  if(msg_end == std::string::npos) return;
  std::string msg_title = message.text.substr(msg_start, msg_end - msg_start);
  std::cerr << "\033[1;33m" << msg_title << "\033[0m" << std::endl;

  //---------------------------
}
void Debug::print_body(vk::validation::Message& message){
  //---------------------------

  //Message body
  size_t msg_start = message.text.find("MessageID = ");
  size_t msg_end = message.text.find(" |", msg_start);

  if(msg_start == std::string::npos || msg_end == std::string::npos){
    std::cerr << message.text << std::endl;
  }else{
    std::string msg_body = message.text.substr(msg_end + 3);
    std::cerr << msg_body << std::endl;
  }

  //---------------------------
}

}
