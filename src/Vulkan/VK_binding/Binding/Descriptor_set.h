#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk::binding{class Uniform;}
namespace vk::binding{class Sampler;}
namespace vk::binding{class Layout;}
namespace vk{class Structure;}
namespace vk::binding::structure{class Binding;}
namespace vk::structure{class Image;}
namespace vk::structure{class Pipeline;}
namespace utl::base{class Data;}


namespace vk::binding{

class Descriptor_set
{
public:
  //Constructor / Destructor
  Descriptor_set(vk::Structure* vk_struct);
  ~Descriptor_set();

public:
  //Main function
  void allocate(vk::binding::structure::Binding* binding);
  void bind(VkCommandBuffer& command_buffer, vk::structure::Pipeline* pipeline, VkDescriptorSet set);
  void clean(vk::binding::structure::Binding* binding);

private:
  vk::Structure* vk_struct;
  vk::binding::Uniform* vk_uniform;
  vk::binding::Sampler* vk_sampler;
  vk::binding::Layout* vk_layout;
};

}
