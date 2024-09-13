#pragma once

#include <vulkan/vulkan.h>

namespace vk{class Structure;}
namespace vk::binding{class Binding;}
namespace vk::draw{class Viewport;}
namespace vk::pipeline{class Shader;}
namespace vk::pipeline{class Vertex;}
namespace vk::pipeline{class Object;}
namespace vk::pipeline{class Layout;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Pipeline;}


namespace vk::pipeline{

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

  //Pipeline creation
  void create_pipeline_struct(vk::structure::Renderpass& renderpass, vk::structure::Pipeline* pipeline);
  void clean_pipeline_struct(vk::structure::Pipeline* pipeline);
  void cmd_bind_pipeline(VkCommandBuffer& command_buffer, vk::structure::Pipeline* pipeline);

private:
  vk::Structure* vk_struct;
  vk::binding::Binding* vk_binding;
  vk::pipeline::Shader* vk_shader;
  vk::pipeline::Vertex* vk_vertex;
  vk::pipeline::Object* vk_object;
  vk::pipeline::Layout* vk_layout;
};

}
