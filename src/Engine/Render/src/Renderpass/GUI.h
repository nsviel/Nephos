#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/fct_timer.h>

namespace eng{class Node;}
namespace vk::main{class Engine;}
namespace vk::main{class Imgui;}
namespace eng::render{class Node;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}


namespace eng::renderpass{

class GUI
{
public:
  //Constructor / Destructor
  GUI(eng::render::Node* node_render);
  ~GUI();

public:
  //Main functions
  void init_renderpass();
  void create_subpass(vk::structure::Renderpass* renderpass);

  void draw(vk::structure::Subpass* subpass);

private:
  vk::main::Engine* vk_engine;
  vk::main::Imgui* vk_imgui;
};

}
