#pragma once

#include <UTL_specific/common.h>

class Struct_vulkan;


class VK_extension
{
public:
  //Constructor / Destructor
  VK_extension(Struct_vulkan* struct_vulkan);
  ~VK_extension();

public:
  //Main functions
  void init();

  //Subfunction
  void extension_instance();
  void extension_window();
  void extension_device();

private:
  Struct_vulkan* struct_vulkan;
};
