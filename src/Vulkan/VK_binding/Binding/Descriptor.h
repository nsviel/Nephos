#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk::binding{class Uniform;}
namespace vk::binding{class Sampler;}
namespace vk::structure{class Vulkan;}
namespace vk::binding::structure{class Binding;}
namespace vk::structure{class Image;}
namespace vk::structure{class Pipeline;}


namespace vk::binding{

class Descriptor
{
public:
  //Constructor / Destructor
  Descriptor(vk::structure::Vulkan* vk_struct);
  ~Descriptor();

public:
  //Main function
  void create_binding(vk::binding::structure::Binding* binding);
  void clean_binding(vk::binding::structure::Binding* binding);

  //Descriptor set update
  void update_descriptor_uniform(vk::binding::structure::Binding* binding);
  void update_descriptor_sampler(vk::binding::structure::Binding* binding, vk::structure::Image* image);

  //Subfunction
  void cmd_bind_descriptor(VkCommandBuffer& command_buffer, vk::structure::Pipeline* pipeline, VkDescriptorSet set);
  void allocate_descriptor_set(vk::binding::structure::Binding* binding);
  void create_layout_from_required(vk::binding::structure::Binding* binding);
  VkDescriptorSetLayout create_layout(std::vector<VkDescriptorSetLayoutBinding>& vec_binding);

private:
  vk::structure::Vulkan* vk_struct;
  vk::binding::Uniform* vk_uniform;
  vk::binding::Sampler* vk_sampler;
};

}