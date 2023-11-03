#ifndef VK_INSTANCE_H
#define VK_INSTANCE_H

#include <ELE_specific/common.h>

class VK_engine;
class VK_validation;
class Struct_vulkan;


class VK_instance
{
public:
  //Constructor / Destructor
  VK_instance(VK_engine* vk_engine);
  ~VK_instance();

public:
  //Main functions
  void init_instance();
  void clean_instance();

  //Subfunction
  void create_instance();

private:
  VK_engine* vk_engine;
  VK_validation* vk_validation;
  Struct_vulkan* struct_vulkan;
};

#endif
