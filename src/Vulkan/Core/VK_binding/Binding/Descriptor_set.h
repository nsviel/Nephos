#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk{class Structure;}
namespace vk::descriptor::structure{class Binding;}
namespace vk::descriptor::structure{class Descriptor_set;}
namespace vk::descriptor::structure{class Layout;}
namespace vk::structure{class Pipeline;}


namespace vk::descriptor{

class Descriptor_set
{
public:
  //Constructor / Destructor
  Descriptor_set(vk::Structure* vk_struct);
  ~Descriptor_set();

public:
  //Main function
  void allocate(vk::descriptor::structure::Descriptor_set& descriptor_set, vk::descriptor::structure::Layout& layout);
  void bind(VkCommandBuffer& command_buffer, vk::structure::Pipeline* pipeline, VkDescriptorSet set);
  void update(vk::descriptor::structure::Descriptor_set& descriptor_set, vk::descriptor::structure::Layout& layout);
  void clean(vk::descriptor::structure::Binding& binding);

private:
  vk::Structure* vk_struct;
};

}
