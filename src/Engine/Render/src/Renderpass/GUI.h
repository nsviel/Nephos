#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/fct_timer.h>

namespace eng{class Node;}
class VK_engine;
class VK_imgui;
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
  VK_engine* vk_engine;
  VK_imgui* vk_imgui;
};

}
