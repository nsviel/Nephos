#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/fct_timer.h>

class VK_engine;
class VK_pipeline;
namespace vk::draw{class Viewport;}
namespace vk::binding{class Descriptor;}
namespace vk::binding{class Uniform;}
namespace vk::draw{class VK_drawing;}
namespace eng::render{class Node;}
namespace eng::shader{class EDL;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}


namespace eng::renderpass{

class EDL
{
public:
  //Constructor / Destructor
  EDL(eng::render::Node* node_render);
  ~EDL();

public:
  //Init functions
  void init_renderpass();
  void create_subpass(vk::structure::Renderpass* renderpass);

  //Draw function
  void draw_edl(vk::structure::Subpass* subpass);
  void update_descriptor(vk::structure::Subpass* subpass);
  void draw_command(vk::structure::Subpass* subpass);

private:
  eng::shader::EDL* shader_edl;
  VK_engine* vk_engine;
  VK_pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
  vk::binding::Descriptor* vk_descriptor;
  vk::binding::Uniform* vk_uniform;
  vk::draw::VK_drawing* vk_drawing;

  Timer timer;
  float time_renderpass;
};

}
