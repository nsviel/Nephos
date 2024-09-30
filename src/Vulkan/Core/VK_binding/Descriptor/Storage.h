#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <string>

namespace vk{class Structure;}
namespace vk::structure{class Descriptor;}
namespace vk::structure{class Layout;}
namespace vk::structure{class Storage;}
namespace vk::structure{class Descriptor_set;}
namespace vk::structure{class Image;}


namespace vk::descriptor{

class Storage
{
public:
  //Constructor / Destructor
  Storage(vk::Structure* vk_struct);
  ~Storage();

public:
  //Main function
  void create_descriptor(vk::structure::Descriptor_set& descriptor_set, vk::structure::Descriptor& descriptor);
  void actualize_storage(vk::structure::Descriptor_set& descriptor_set);
  void actualize_storage(vk::structure::Descriptor_set& descriptor_set, vk::structure::Storage& storage, vk::structure::Image& image);

  //Subfunction
  std::shared_ptr<vk::structure::Storage> query_storage(vk::structure::Descriptor_set& descriptor_set, std::string name);

private:
  vk::Structure* vk_struct;
};

}
