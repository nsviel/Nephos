#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}


namespace vk::thread{

class Thread
{
public:
  //Constructor / Destructor
  Thread(vk::structure::Vulkan* struct_vulkan);
  ~Thread();

public:
  //Main functions

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
