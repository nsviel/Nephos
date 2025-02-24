#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <string>

namespace vk{class Structure;}
namespace vk::structure{class Descriptor;}
namespace vk::structure{class Layout;}
namespace vk::structure{class Sampler;}
namespace vk::structure{class Descriptor_set;}
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
  void create_descriptor(vk::structure::Descriptor_set& descriptor_set, vk::structure::Descriptor& descriptor);
  void update_sampler(vk::structure::Descriptor_set& descriptor_set);
  void update_sampler(vk::structure::Descriptor_set& descriptor_set, vk::structure::Sampler& sampler, vk::structure::Image& image);

  //Subfunction
  std::shared_ptr<vk::structure::Sampler> query_sampler(vk::structure::Descriptor_set& descriptor_set, std::string name);

private:
  vk::Structure* vk_struct;
};

}
