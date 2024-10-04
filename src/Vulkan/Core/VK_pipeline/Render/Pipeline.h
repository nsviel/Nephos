#pragma once

#include <vulkan/vulkan.h>
#include <memory>

namespace vk{class Structure;}
namespace vk::presentation{class Viewport;}
namespace vk::synchro{class Synchro;}
namespace vk::render{class Component;}
namespace vk::pipeline{class Descriptor;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Pipeline;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Descriptor_set;}


namespace vk::render{

class Pipeline
{
public:
  //Constructor / Destructor
  Pipeline(vk::Structure* vk_struct);
  ~Pipeline();

public:
  //Main function
  void create_pipeline(vk::structure::Renderpass& renderpass);
  void clean_pipeline(vk::structure::Renderpass& renderpass);
  void recreate_pipeline(vk::structure::Renderpass& renderpass, vk::structure::Pipeline& pipeline);

  //Subfunction
  void add_pipeline_topology(vk::structure::Subpass& subpass, std::shared_ptr<vk::structure::Pipeline>);
  void cmd_bind_pipeline(VkCommandBuffer& command_buffer, vk::structure::Pipeline& pipeline);
  void cmd_bind_descriptor_set(VkCommandBuffer& command_buffer, vk::structure::Pipeline& pipeline, vk::structure::Descriptor_set& descriptor_set);

private:
  vk::Structure* vk_struct;
  vk::pipeline::Descriptor* vk_descriptor;
  vk::render::Component* vk_component;
  vk::synchro::Synchro* vk_synchro;
};

}
