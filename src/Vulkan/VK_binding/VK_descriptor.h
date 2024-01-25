#pragma once

#include <Utility/Specific/common.h>

namespace vk::binding{class VK_uniform;}
namespace vk::binding{class VK_sampler;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Binding;}
namespace vk::structure{class Image;}
namespace vk::structure{class Pipeline;}


namespace vk::binding{

class VK_descriptor
{
public:
  //Constructor / Destructor
  VK_descriptor(vk::structure::Vulkan* struct_vulkan);
  ~VK_descriptor();

public:
  //Main functions
  void create_binding(vk::structure::Binding* binding);
  void clean_binding(vk::structure::Binding* binding);

  //Descriptor set update
  void update_descriptor_uniform(vk::structure::Binding* binding);
  void update_descriptor_sampler(vk::structure::Binding* binding, vector<vk::structure::Image*> vec_image);
  void update_descriptor_sampler(vk::structure::Binding* binding, vk::structure::Image* image);

  //Subfunction
  void cmd_bind_descriptor(VkCommandBuffer& command_buffer, vk::structure::Pipeline* pipeline, VkDescriptorSet set);
  void allocate_descriptor_set(vk::structure::Binding* binding);
  void create_layout_from_required(vk::structure::Binding* binding);
  VkDescriptorSetLayout create_layout(vector<VkDescriptorSetLayoutBinding>& vec_binding);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::binding::VK_uniform* vk_uniform;
  vk::binding::VK_sampler* vk_sampler;
};

}
