#pragma once

#include <Utility/Specific/common.h>

namespace vk{class Node;}
namespace vk::main{class VK_engine;}
namespace vk::main{class VK_imgui;}
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
  vk::main::VK_imgui* vk_imgui;
  vk::main::VK_engine* vk_engine;
};

}
