#pragma once

#include <Utility/Specific/common.h>

namespace vk{class Node;}
namespace vk::main{class Graphical;}
namespace vk::main{class Imgui;}
namespace vk::render{class Node;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}


namespace vk::renderpass{

class GUI
{
public:
  //Constructor / Destructor
  GUI(vk::Node* node_vulkan);
  ~GUI();

public:
  //Main functions
  void init_renderpass();
  void create_subpass(vk::structure::Renderpass* renderpass);

  void draw(vk::structure::Subpass* subpass);

private:
  vk::main::Graphical* vk_graphical;
  vk::main::Imgui* vk_imgui;
};

}
