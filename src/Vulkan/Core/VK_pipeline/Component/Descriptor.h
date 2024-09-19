#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk{class Structure;}
namespace vk::descriptor{class Uniform;}
namespace vk::descriptor{class Sampler;}
namespace vk::descriptor{class Layout;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk::descriptor::structure{class Binding;}
namespace vk::structure{class Pipeline;}


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

private:
  vk::descriptor::Uniform* vk_uniform;
  vk::descriptor::Sampler* vk_sampler;
  vk::descriptor::Layout* vk_layout;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
};

}