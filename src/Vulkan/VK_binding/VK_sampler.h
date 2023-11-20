#ifndef VK_SAMPLER_H
#define VK_SAMPLER_H

#include <VK_struct/Struct_vk_binding.h>
#include <VK_struct/Struct_pipeline.h>
#include <UTL_specific/common.h>

class Struct_vulkan;


class VK_sampler
{
public:
  //Constructor / Destructor
  VK_sampler(Struct_vulkan* struct_vulkan);
  ~VK_sampler();

public:
  //Main functions
  void create_sampler(Struct_vk_binding* binding);
  Struct_vk_sampler* create_sampler_obj(string name, int binding, VkDescriptorType type);

private:
  Struct_vulkan* struct_vulkan;
};

#endif
