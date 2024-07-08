#pragma once

#include <vulkan/vulkan.h>
#include <string>


namespace vk::validation{

class LOG_debug
{
public:
  static LOG_debug& get_instance(){
    static LOG_debug instance;
    return instance;
  }

  //Main function
  void print_validation_error(std::string message);

  //Subfunction
  void print_header(std::string message);
  void print_message_ID(std::string message);

private:
  LOG_debug() = default;
};

}
