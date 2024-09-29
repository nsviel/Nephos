#pragma once

#include <vulkan/vulkan.h>

namespace vk{class Structure;}
namespace vk::pipeline{class Layout;}
namespace vk::shader{class Module;}
namespace vk::pipeline{class Vertex;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Pipeline;}


namespace vk::render{

class Component
{
public:
  //Constructor / Destructor
  Component(vk::Structure* vk_struct);
  ~Component();

public:
  //Main function
  void create_pipeline_component(vk::structure::Renderpass& renderpass, vk::structure::Pipeline& pipeline);
  void clean_pipeline_component(vk::structure::Pipeline& pipeline);

  //Subfunction
  void info_pipeline_topology(vk::structure::Pipeline& pipeline);
  void info_pipeline_dynamic(vk::structure::Pipeline& pipeline);
  void info_pipeline_viewport(vk::structure::Pipeline& pipeline);
  void info_pipeline_rasterization(vk::structure::Pipeline& pipeline);
  void info_pipeline_multisampling(vk::structure::Pipeline& pipeline);
  void info_pipeline_blend_attachment(vk::structure::Pipeline& pipeline);
  void info_pipeline_blend(vk::structure::Pipeline& pipeline);
  void info_pipeline_depth_stencil(vk::structure::Pipeline& pipeline);

  //Creation function
  void create_pipeline_handle(vk::structure::Renderpass& renderpass, vk::structure::Pipeline& pipeline);
  void clean_pipeline_handle(vk::structure::Pipeline& pipeline);

private:
  vk::Structure* vk_struct;
  vk::shader::Module* vk_shader;
  vk::pipeline::Vertex* vk_vertex;
  vk::pipeline::Layout* vk_layout;
};

}
