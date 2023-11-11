#ifndef VK_PRESENTATION_H
#define VK_PRESENTATION_H

#include <ELE_specific/common.h>

class Struct_vulkan;


class VK_presentation
{
public:
  //Constructor / Destructor
  VK_presentation(Struct_vulkan* struct_vulkan);
  ~VK_presentation();

public:
  //Main functions

private:
  Struct_vulkan* struct_vulkan;
};

#endif
