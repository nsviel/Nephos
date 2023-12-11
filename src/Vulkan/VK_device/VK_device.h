#pragma once

#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>


class VK_physical_device;


class VK_device
{
public:
  //Constructor / Destructor
  VK_device(vk::structure::Vulkan* struct_vulkan);
  ~VK_device();

public:
  //Main functions
  void init();
  void clean();

  //Subfunction
  void create_logical_device();
  void find_device_queue_handles();

private:
  vk::structure::Vulkan* struct_vulkan;
  VK_physical_device* vk_physical_device;
};
