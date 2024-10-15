#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace vk::validation{class Message;}


namespace vk::validation::log{

class Debug
{
public:
  Debug();
  ~Debug();

public:
  //Main function
  void print_message(vk::validation::Message& message);

  //Subfunction
  void print_header(vk::validation::Message& message);
  void print_body(vk::validation::Message& message);

private:
};

}
