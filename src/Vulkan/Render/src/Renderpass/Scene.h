#pragma once

#include <Utility/Specific/common.h>

namespace vk{class Node;}
namespace vk::main{class Graphical;}
namespace vk::renderpass{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::binding{class Descriptor;}
namespace vk::binding{class Uniform;}
namespace vk::draw{class Graphical;}
namespace vk::render{class Node;}
namespace vk::render{class Scene;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}


namespace vk::renderpass{

class Scene
{
public:
  //Constructor / Destructor
  Scene(vk::Node* node_vulkan);
  ~Scene();

public:
  //Init functions
  void init_renderpass();
  void create_subpass(vk::structure::Renderpass* renderpass);

  //Draw function
  void draw_scene(vk::structure::Subpass* subpass);
  void cmd_draw_point(vk::structure::Subpass* subpass);
  void cmd_draw_line(vk::structure::Subpass* subpass);
  void cmd_draw_triangle(vk::structure::Subpass* subpass);

private:
  vk::render::Scene* shader_scene;
  vk::render::Node* node_render;
  vk::structure::Vulkan* struct_vulkan;
  vk::binding::Descriptor* vk_descriptor;
  vk::binding::Uniform* vk_uniform;
  vk::draw::Graphical* vk_drawing;
  vk::main::Graphical* vk_graphical;
  vk::renderpass::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
};

}
