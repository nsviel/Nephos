#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace vk{class Structure;}
namespace vk::binding::structure{class Required;}
namespace vk::binding::structure{class Binding;}
namespace vk::binding::structure{class Sampler;}


namespace vk::binding{

class Sampler
{
public:
  //Constructor / Destructor
  Sampler(vk::Structure* vk_struct);
  ~Sampler();

public:
  //Main function
  void create_sampler(vk::binding::structure::Binding* binding);
  vk::binding::structure::Sampler* create_sampler_obj(std::string name, int binding, VkDescriptorType type);

  //Subfunction
  vk::binding::structure::Required sampler_color();
  vk::binding::structure::Required sampler_depth();

private:
  vk::Structure* vk_struct;
};

}
