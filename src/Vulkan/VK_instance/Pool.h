#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}


namespace vk::instance{

class Pool
{
public:
  //Constructor / Destructor
  Pool(vk::structure::Vulkan* struct_vulkan);
  ~Pool();

public:
  //Main functions
  void init();
  void clean();

  //Descriptor pool
  void create_descriptor_pool();
  void reset_descriptor_pool();
  void clean_descriptor_pool();

  //Command pool
  void create_command_pool();
  void reset_command_pool();
  void clean_command_pool();

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
