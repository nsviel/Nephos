#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace vk{class Structure;}
namespace vk::binding::structure{class Descriptor;}
namespace vk::binding::structure{class Binding;}
namespace vk::binding::structure{class Sampler;}
namespace vk::structure{class Image;}


namespace vk::binding{

class Sampler
{
public:
  //Constructor / Destructor
  Sampler(vk::Structure* vk_struct);
  ~Sampler();

public:
  //Main function
  void create_sampler(vk::binding::structure::Binding& binding);
  void update_sampler(vk::binding::structure::Binding& binding, vk::structure::Image* image);

  //Subfunction
  vk::binding::structure::Sampler* query_sampler(std::string& name);

private:
  vk::Structure* vk_struct;
};

}
