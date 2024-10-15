#pragma once

#include <string>


namespace vk::validation::log{

//Singleton class to store Shader printf output
class Shader
{
public:
  Shader();
  ~Shader();

public:
  //Main function
  void print_message(std::string message);

  //Subfunction
  void print_header(std::string message);
  void print_message_ID(std::string message);

private:
};

}
