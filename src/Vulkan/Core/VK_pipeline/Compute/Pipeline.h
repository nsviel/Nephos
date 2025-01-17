#pragma once

#include <vulkan/vulkan.h>
#include <memory>

namespace vk{class Structure;}
namespace vk::synchro{class Synchro;}
namespace vk::pipeline::compute{class Component;}
namespace vk::pipeline{class Descriptor;}
namespace vk::structure{class Pipeline;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Descriptor_set;}
namespace utl::base{class Texture;}


namespace vk::pipeline::compute{

class Pipeline
{
public:
  //Constructor / Destructor
  Pipeline(vk::Structure* vk_struct);
  ~Pipeline();

public:
  //Main function
  void init();
  void reset();
  void clean();

  //Subfunction
  void recreate_pipeline(vk::structure::Pipeline& pipeline);
  void cmd_bind_pipeline(VkCommandBuffer& command_buffer, vk::structure::Pipeline& pipeline);
  void cmd_dispatch_pipeline(VkCommandBuffer& command_buffer, utl::base::Texture& texture);
  void cmd_bind_descriptor_set(VkCommandBuffer& command_buffer, vk::structure::Pipeline& pipeline, vk::structure::Descriptor_set& descriptor_set);

private:
  vk::Structure* vk_struct;
  vk::pipeline::Descriptor* vk_descriptor;
  vk::pipeline::compute::Component* vk_component;
  vk::synchro::Synchro* vk_synchro;
};

}
