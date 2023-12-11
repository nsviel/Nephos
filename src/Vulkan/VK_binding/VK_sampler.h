#pragma once

#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>




class VK_sampler
{
public:
  //Constructor / Destructor
  VK_sampler(vk::structure::Struct_vulkan* struct_vulkan);
  ~VK_sampler();

public:
  //Main functions
  void create_sampler(vk::structure::Binding* binding);
  vk::structure::Sampler* create_sampler_obj(string name, int binding, VkDescriptorType type);

private:
  vk::structure::Struct_vulkan* struct_vulkan;
};
