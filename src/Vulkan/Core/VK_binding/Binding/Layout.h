#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk::binding{class Uniform;}
namespace vk::binding{class Sampler;}
namespace vk{class Structure;}
namespace vk::binding::structure{class Binding;}
namespace vk::structure{class Image;}
namespace vk::structure{class Pipeline;}
namespace utl::base{class Data;}


namespace vk::binding{

class Layout
{
public:
  //Constructor / Destructor
  Layout(vk::Structure* vk_struct);
  ~Layout();

public:
  //Main function
  void create_layout(vk::binding::structure::Binding& binding);
  void clean_layout(vk::binding::structure::Binding& binding);

  //Subfunction
  void make_required_binding(vk::binding::structure::Binding& binding, std::vector<VkDescriptorSetLayoutBinding>& vec_binding);
  void create_layout(vk::binding::structure::Binding& binding, std::vector<VkDescriptorSetLayoutBinding>& vec_binding);

private:
  vk::Structure* vk_struct;
};

}
