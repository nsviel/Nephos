#ifndef VK_ERROR_H
#define VK_ERROR_H

#include "../VK_struct/struct_binding.h"
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;


class VK_error
{
public:
  //Constructor / Destructor
  VK_error(VK_engine* vk_engine);
  ~VK_error();

public:
  //Binding error
  void uniform_name_not_recognized(Struct_binding* binding, string name);
  void sampler_name_not_recognized(Struct_binding* binding, string name);

private:
  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;

};

#endif
