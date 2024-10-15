#include "Shader.h"

#include <Utility/Namespace.h>
#include <iostream>
#include <string>


namespace vk::validation::log{

//Constructor / Destructor
Shader::Shader(){}
Shader::~Shader(){}

//Main function
void Shader::print_message(std::string message){
  //---------------------------

  this->print_header(message);
  this->print_message_ID(message);

  //---------------------------
}

//Subfunction
void Shader::print_header(std::string message){
  //---------------------------

  std::cout << "--------------------------" << std::endl;
  std::cout << "[" << "\033[1;32mVL\033[0m] [\033[1;33mSHADER\033[0m]" << std::endl;

  //---------------------------
}
void Shader::print_message_ID(std::string message){
  //---------------------------

  // Find the position of "[SHADER]"
   size_t pos = message.find("[SHADER]");
   if(pos != std::string::npos){
     message = message.substr(pos + std::string("[SHADER]").length());
   }

   //Print message
  std::cout << message << std::endl;

  //---------------------------
}

}
