#ifndef VK_EXTENSION_H
#define VK_EXTENSION_H

#include <ELE_specific/common.h>

class Struct_vulkan;


class VK_extension
{
public:
  //Constructor / Destructor
  VK_extension(Struct_vulkan* struct_vulkan);
  ~VK_extension();

public:
  //Main functions

private:
  Struct_vulkan* struct_vulkan;
};

#endif
