#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk{class Structure;}
namespace vk::descriptor{class Uniform;}
namespace vk::descriptor{class Sampler;}
namespace vk::descriptor{class Storage;}
namespace vk::structure{class Descriptor_set;}
namespace vk::structure{class Layout;}
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
  void allocate_descriptor_set(vk::structure::Descriptor_set& descriptor_set, vk::structure::Layout& layout);
  void clean_descriptor_set(vk::structure::Descriptor_set& descriptor_set);

  //Subfunction
  void allocate_handle(vk::structure::Descriptor_set& descriptor_set, vk::structure::Layout& layout);
  void free_handle(vk::structure::Descriptor_set& descriptor_set);
  void create_descriptor(vk::structure::Descriptor_set& descriptor_set, vk::structure::Layout& layout);
  void update_descriptor_set(vk::structure::Descriptor_set& descriptor_set, vk::structure::Layout& layout);

private:
  vk::Structure* vk_struct;
  vk::descriptor::Uniform* vk_uniform;
  vk::descriptor::Sampler* vk_sampler;
  vk::descriptor::Storage* vk_storage;
};

}
