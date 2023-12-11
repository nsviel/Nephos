#pragma once

#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>

class VK_validation;



class VK_instance
{
public:
  //Constructor / Destructor
  VK_instance(vk::structure::Vulkan* struct_vulkan);
  ~VK_instance();

public:
  //Main functions
  void init_instance();
  void clean_instance();

  //Subfunction
  void create_instance();

private:
  VK_validation* vk_validation;
  vk::structure::Vulkan* struct_vulkan;
};
