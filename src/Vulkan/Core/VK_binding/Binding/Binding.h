#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk{class Structure;}
namespace vk::binding{class Uniform;}
namespace vk::binding{class Sampler;}
namespace vk::binding{class Layout;}
namespace vk::binding{class Descriptor_set;}
namespace vk::structure{class Image;}
namespace vk::structure{class Pipeline;}
namespace vk::binding::structure{class Binding;}
namespace vk::binding::structure{class Layout;}
namespace utl::base{class Data;}


namespace vk::binding{

class Binding
{
public:
  //Constructor / Destructor
  Binding(vk::Structure* vk_struct);
  ~Binding();

public:
  //Main function
  void create_layout(vk::binding::structure::Layout& layout);
  void create_binding(vk::binding::structure::Binding& binding);
  void clean_binding(vk::binding::structure::Binding& binding);

  //Subfunction
  void create_descriptor(vk::binding::structure::Binding& binding);

private:
  vk::Structure* vk_struct;
  vk::binding::Uniform* vk_uniform;
  vk::binding::Sampler* vk_sampler;
  vk::binding::Layout* vk_layout;
  vk::binding::Descriptor_set* vk_descriptor_set;
};

}
