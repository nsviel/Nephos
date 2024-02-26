#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}


namespace vk::synchro{

class Synchro
{
public:
  //Constructor / Destructor
  Synchro(vk::structure::Vulkan* struct_vulkan);
  ~Synchro();

public:
  //Main function
  void wait_idle();
  void end_idle();

private:
  vk::structure::Vulkan* struct_vulkan;
};

}