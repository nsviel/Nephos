#pragma once

#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Binding;}
namespace vk::structure{class Sampler;}


namespace vk::binding{

class Sampler
{
public:
  //Constructor / Destructor
  Sampler(vk::structure::Vulkan* struct_vulkan);
  ~Sampler();

public:
  //Main functions
  void create_sampler(vk::structure::Binding* binding);
  vk::structure::Sampler* create_sampler_obj(string name, int binding, VkDescriptorType type);

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
