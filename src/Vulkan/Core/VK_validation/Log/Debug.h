#pragma once

#include <vulkan/vulkan.h>
#include <string>


namespace vk::validation::log{

class Debug
{
public:
  Debug();
  ~Debug();

public:
  //Main function
  void print_message(std::string message);

  //Subfunction
  void print_header(std::string message);
  void print_severity(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity);
  void print_message_ID(std::string message);

private:
};

}
