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

class Descriptor
{
public:
  //Constructor / Destructor
  Descriptor(vk::Structure* vk_struct);
  ~Descriptor();

public:
  //Main function
  void create_binding(vk::binding::structure::Binding* binding);
  void clean_binding(vk::binding::structure::Binding* binding);

  //Subfunction
  void cmd_bind_descriptor(VkCommandBuffer& command_buffer, vk::structure::Pipeline* pipeline, VkDescriptorSet set);
  void allocate_descriptor_set(vk::binding::structure::Binding* binding);
  void make_required_descriptor(utl::base::Data& data, vk::binding::structure::Binding* binding);

private:
  vk::Structure* vk_struct;
  vk::binding::Uniform* vk_uniform;
  vk::binding::Sampler* vk_sampler;
  vk::binding::Layout* vk_layout;
};

}
