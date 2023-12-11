#pragma once

#include <UTL_specific/common.h>

class VK_validation;
class Struct_vulkan;


class VK_instance
{
public:
  //Constructor / Destructor
  VK_instance(Struct_vulkan* struct_vulkan);
  ~VK_instance();

public:
  //Main functions
  void init_instance();
  void clean_instance();

  //Subfunction
  void create_instance();

private:
  VK_validation* vk_validation;
  Struct_vulkan* struct_vulkan;
};
