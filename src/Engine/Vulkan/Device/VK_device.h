#ifndef VK_DEVICE_H
#define VK_DEVICE_H

#include <Specific/common.h>

class VK_engine;
class VK_struct;
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
  VK_struct* vk_struct;
  VK_physical_device* vk_physical_device;
};

#endif
