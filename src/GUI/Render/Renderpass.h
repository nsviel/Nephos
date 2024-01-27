#pragma once

#include <Utility/Specific/common.h>

namespace vk{class Node;}
namespace vk::main{class Engine;}
namespace vk::main{class Imgui;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Subpass;}


namespace gui{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(vk::Node* vulkan);
  ~Renderpass();

public:
  //Main functions
  void init_renderpass();
  void create_subpass(vk::structure::Renderpass* renderpass);

  //Draw function
  void draw(vk::structure::Subpass* subpass);

private:
  vk::main::Imgui* vk_imgui;
  vk::main::Engine* vk_engine;
};

}
