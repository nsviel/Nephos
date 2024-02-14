#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}


namespace vk::thread{

class Transfer
{
public:
  //Constructor / Destructor
  Transfer(vk::structure::Vulkan* struct_vulkan);
  ~Transfer();

public:
  //Main functions
  void submitToTransferQueue(VkDevice device, VkQueue transferQueue);

private:
  vk::structure::Vulkan* struct_vulkan;

  std::thread thread;
};

}
