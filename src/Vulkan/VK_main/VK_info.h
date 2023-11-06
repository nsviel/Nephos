#ifndef VK_INFO_H
#define VK_INFO_H

#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;


class VK_info
{
public:
  //Constructor / Destructor
  VK_info(VK_engine* vk_engine);
  ~VK_info();

public:
  //Main functions

private:
  Struct_vulkan* struct_vulkan;

};

#endif
