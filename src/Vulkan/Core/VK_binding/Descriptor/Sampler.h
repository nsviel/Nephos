#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <string>

namespace vk{class Structure;}
namespace vk::descriptor::structure{class Descriptor;}
namespace vk::descriptor::structure{class Binding;}
namespace vk::descriptor::structure{class Layout;}
namespace vk::descriptor::structure{class Sampler;}
namespace vk::descriptor::structure{class Descriptor_set;}
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
  void create_sampler(vk::descriptor::structure::Descriptor_set& descriptor_set, vk::descriptor::structure::Descriptor& descriptor);
  void actualize_sampler(vk::descriptor::structure::Descriptor_set& descriptor_set);
  void actualize_sampler(vk::descriptor::structure::Descriptor_set& descriptor_set, vk::descriptor::structure::Sampler& sampler, vk::structure::Image& image);

  //Subfunction
  std::shared_ptr<vk::descriptor::structure::Sampler> query_sampler(vk::descriptor::structure::Descriptor_set& descriptor_set, std::string name);

private:
  vk::Structure* vk_struct;
};

}
