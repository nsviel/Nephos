#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>


class VK_profiler
{
public:
  //Constructor / Destructor
  VK_profiler(vk::structure::Vulkan* struct_vulkan);
  ~VK_profiler();

public:
  //Main functions

private:
  vk::structure::Vulkan* struct_vulkan;
};
