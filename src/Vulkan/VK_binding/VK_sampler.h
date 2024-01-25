#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Binding;}
namespace vk::structure{class Sampler;}


class VK_sampler
{
public:
  //Constructor / Destructor
  VK_sampler(vk::structure::Vulkan* struct_vulkan);
  ~VK_sampler();

public:
  //Main functions
  void create_sampler(vk::structure::Binding* binding);
  vk::structure::Sampler* create_sampler_obj(string name, int binding, VkDescriptorType type);

private:
  vk::structure::Vulkan* struct_vulkan;
};
