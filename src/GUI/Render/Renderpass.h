#pragma once

#include <Utility/Specific/common.h>

class Vulkan;
class VK_engine;
class VK_imgui;
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Subpass;}


namespace gui{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(Vulkan* vulkan);
  ~Renderpass();

public:
  //Main functions
  void init_renderpass();
  void create_subpass(vk::structure::Renderpass* renderpass);

  //Draw function
  void draw(vk::structure::Subpass* subpass);

private:
  VK_imgui* vk_imgui;
  VK_engine* vk_engine;
};

}
