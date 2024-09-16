#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace vk{class Structure;}
namespace vk::descriptor::structure{class Descriptor;}
namespace vk::descriptor::structure{class Binding;}
namespace vk::descriptor::structure{class Layout;}
namespace vk::descriptor::structure{class Sampler;}
namespace vk::structure{class Image;}


namespace vk::descriptor{

class Sampler
{
public:
  //Constructor / Destructor
  Sampler(vk::Structure* vk_struct);
  ~Sampler();

public:
  //Main function
  void create_sampler(vk::descriptor::structure::Layout& layout, vk::descriptor::structure::Descriptor& descriptor);
  void update_sampler(vk::descriptor::structure::Binding& binding, vk::structure::Image* image);

  //Subfunction
  vk::descriptor::structure::Sampler* query_sampler(vk::descriptor::structure::Binding& binding, std::string& name);

private:
  vk::Structure* vk_struct;
};

}
