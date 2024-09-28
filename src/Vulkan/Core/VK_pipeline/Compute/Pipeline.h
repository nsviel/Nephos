#pragma once

#include <vulkan/vulkan.h>
#include <memory>

namespace vk{class Structure;}
namespace vk::synchro{class Synchro;}
namespace vk::compute{class Component;}
namespace vk::pipeline{class Descriptor;}
namespace vk::structure{class Pipeline;}
namespace vk::structure{class Subpass;}


namespace vk::compute{

class Pipeline
{
public:
  //Constructor / Destructor
  Pipeline(vk::Structure* vk_struct);
  ~Pipeline();

public:
  //Main function
  void create_pipeline(std::shared_ptr<vk::structure::Pipeline> pipeline);
  void clean_pipeline();
  void recreate_pipeline(vk::structure::Pipeline& pipeline);

  //Subfunction
  void cmd_bind_pipeline(VkCommandBuffer& command_buffer, vk::structure::Pipeline& pipeline);

private:
  vk::Structure* vk_struct;
  vk::pipeline::Descriptor* vk_descriptor;
  vk::compute::Component* vk_component;
  vk::synchro::Synchro* vk_synchro;
};

}
