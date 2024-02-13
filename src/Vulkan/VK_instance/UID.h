#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}


namespace vk::instance{

class UID
{
public:
  //Constructor / Destructor
  UID(vk::structure::Vulkan* struct_vulkan);
  ~UID();

public:
  //Main functions


private:
  vk::structure::Vulkan* struct_vulkan;
};

}
