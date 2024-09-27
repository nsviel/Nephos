#pragma once

#include <string>


namespace vk::validation::log{

//Singleton class to store Shader printf output
class Shader
{
public:
  static Shader& get_instance(){
    static Shader instance;
    return instance;
  }

public:
  //Main function
  void print_message(std::string message);

  //Subfunction
  void print_header(std::string message);
  void print_message_ID(std::string message);

private:
  Shader() = default;
};

}
