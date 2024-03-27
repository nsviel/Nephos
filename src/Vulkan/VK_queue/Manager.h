#pragma once

#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}


namespace vk::queue{

class Manager
{
public:
  //Constructor / Destructor
  Manager(vk::structure::Vulkan* struct_vulkan);
  ~Manager();

public:
  //Main functions
  void init();
  
private:
  vk::structure::Vulkan* struct_vulkan;
};

}
