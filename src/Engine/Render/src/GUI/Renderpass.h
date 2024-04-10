#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace vk::main{class Engine;}
namespace vk::gui{class Imgui;}
namespace eng::render{class Node;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}


namespace rnd::gui{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(eng::render::Node* node_render);
  ~Renderpass();

public:
  //Main functions
  void init_renderpass();
  void create_subpass(vk::structure::Renderpass* renderpass);

  void draw(vk::structure::Subpass* subpass);

private:
  vk::main::Engine* vk_engine;
  vk::gui::Imgui* vk_imgui;
};

}
