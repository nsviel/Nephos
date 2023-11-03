#ifndef VK_DEVICE_H
#define VK_DEVICE_H

#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_physical_device;


class VK_device
{
public:
  //Constructor / Destructor
  VK_device(VK_engine* vk_engine);
  ~VK_device();

public:
  //Main functions
  void create_logical_device();
  void clean_logical_device();

private:
  Struct_vulkan* vk_struct;
  VK_physical_device* vk_physical_device;
};

#endif
