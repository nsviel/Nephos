#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Binding;}
namespace vk::structure{class Sampler;}


namespace vk::binding{

class Sampler
{
public:
  //Constructor / Destructor
  Sampler(vk::structure::Vulkan* vk_struct);
  ~Sampler();

public:
  //Main function
  void create_sampler(vk::structure::Binding* binding);
  vk::structure::Sampler* create_sampler_obj(std::string name, int binding, VkDescriptorType type);

private:
  vk::structure::Vulkan* vk_struct;
};

}
