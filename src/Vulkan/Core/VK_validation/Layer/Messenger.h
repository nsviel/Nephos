#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <string>

namespace vk{class Structure;}


namespace vk::validation{

class Messenger
{
public:
  //Constructor / Destructor
  Messenger(vk::Structure* vk_struct);
  ~Messenger();

public:
  //Main function
  void create_messenger_info();
  void setup_messenger_function();
  void clean_messenger_function();

private:
  vk::Structure* vk_struct;
};

}
