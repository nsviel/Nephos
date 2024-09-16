#pragma once

#include <vulkan/vulkan.h>
#include <string>


namespace vk::validation::log{

class Debug
{
public:
  static Debug& get_instance(){
    static Debug instance;
    return instance;
  }

  //Main function
  void print_validation_error(std::string message);

  //Subfunction
  void print_header(std::string message);
  void print_message_ID(std::string message);

private:
  Debug() = default;
};

}
