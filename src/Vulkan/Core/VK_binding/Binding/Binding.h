#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk{class Structure;}
namespace vk::descriptor{class Uniform;}
namespace vk::descriptor{class Sampler;}
namespace vk::descriptor{class Layout;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk::structure{class Image;}
namespace vk::structure{class Pipeline;}
namespace vk::descriptor::structure{class Binding;}
namespace vk::descriptor::structure{class Layout;}
namespace utl::base{class Data;}


namespace vk::descriptor{

class Binding
{
public:
  //Constructor / Destructor
  Binding(vk::Structure* vk_struct);
  ~Binding();

public:
  //Main function
  void create_binding(vk::descriptor::structure::Binding& binding);
  void clean_binding(vk::descriptor::structure::Binding& binding);


private:
  vk::Structure* vk_struct;
  vk::descriptor::Uniform* vk_uniform;
  vk::descriptor::Sampler* vk_sampler;
  vk::descriptor::Layout* vk_layout;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
};

}
