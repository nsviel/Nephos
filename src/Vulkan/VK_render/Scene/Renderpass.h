#pragma once

#include <Utility/Specific/Common.h>

namespace vk::main{class Engine;}
namespace vk::renderpass{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::binding{class Descriptor;}
namespace vk::binding{class Uniform;}
namespace vk::binding{class Type;}
namespace vk::draw{class Drawer;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}
namespace vk::render::scene{class Shader;}


namespace vk::render::scene{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(vk::structure::Vulkan* vk_struct);
  ~Renderpass();

public:
  //Init functions
  void init_renderpass();
  void create_subpass(vk::structure::Renderpass* renderpass);

  //Draw function
  void draw_scene(vk::structure::Subpass* subpass);
  void cmd_draw_point(vk::structure::Subpass* subpass);
  void cmd_draw_line(vk::structure::Subpass* subpass);
  void cmd_draw_triangle(vk::structure::Subpass* subpass);

  //Subfunction
  bool check_data(utl::base::Data* data, int typology);

private:
  vk::structure::Vulkan* vk_struct;
  vk::binding::Descriptor* vk_descriptor;
  vk::binding::Uniform* vk_uniform;
  vk::draw::Drawer* vk_drawer;
  vk::main::Engine* vk_engine;
  vk::renderpass::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
  vk::binding::Type* vk_type;
  vk::render::scene::Shader* shader_scene;
};

}
