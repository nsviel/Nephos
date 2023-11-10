#ifndef VK_SAMPLER_H
#define VK_SAMPLER_H

#include <VK_struct/Struct_binding.h>
#include <VK_struct/Struct_pipeline.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_buffer;


class VK_sampler
{
public:
  //Constructor / Destructor
  VK_sampler(Struct_vulkan* struct_vulkan);
  ~VK_sampler();

public:
  //Main functions
  void create_sampler(Struct_binding* binding);
  Struct_sampler* create_sampler_obj(string name, int binding, VkDescriptorType type);

private:
  Struct_vulkan* struct_vulkan;
  VK_buffer* vk_buffer;
};

#endif
