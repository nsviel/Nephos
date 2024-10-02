#pragma once

#include <vulkan/vulkan.h>
#include <memory>

namespace vk{class Structure;}
namespace vk::descriptor{class Uniform;}
namespace vk::descriptor{class Sampler;}
namespace vk::descriptor{class Layout;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk::structure{class Pipeline;}
namespace vk::structure{class Descriptor_set;}


namespace vk::pipeline{

class Descriptor
{
public:
  //Constructor / Destructor
  Descriptor(vk::Structure* vk_struct);
  ~Descriptor();

public:
  //Main function
  void create_pipeline_descriptor(vk::structure::Pipeline& pipeline);
  void clean_pipeline_descriptor(vk::structure::Pipeline& pipeline);

  //Subfunction
  void create_descriptor_set_pool(vk::structure::Pipeline& pipeline);
  void clean_descriptor_set_pool(vk::structure::Pipeline& pipeline);
  std::shared_ptr<vk::structure::Descriptor_set> query_descriptor_set(vk::structure::Pipeline& pipeline);

private:
  vk::descriptor::Uniform* vk_uniform;
  vk::descriptor::Sampler* vk_sampler;
  vk::descriptor::Layout* vk_layout;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
};

}
