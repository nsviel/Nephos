#ifndef VK_DEVICE_H
#define VK_DEVICE_H

#include <UTL_specific/common.h>

class Struct_vulkan;
class VK_physical_device;


class VK_device
{
public:
  //Constructor / Destructor
  VK_device(Struct_vulkan* struct_vulkan);
  ~VK_device();

public:
  //Main functions
  void init();
  void clean();

  //Subfunction
  void create_logical_device();
  void find_device_queue_handles();

private:
  Struct_vulkan* struct_vulkan;
  VK_physical_device* vk_physical_device;
};

#endif
