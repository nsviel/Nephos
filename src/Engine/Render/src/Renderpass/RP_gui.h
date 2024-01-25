#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/fct_timer.h>

class Engine;
class VK_engine;
class VK_imgui;
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}


namespace eng::renderpass{

class RP_gui
{
public:
  //Constructor / Destructor
  RP_gui(Engine* engine);
  ~RP_gui();

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
