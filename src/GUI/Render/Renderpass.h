#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>

class Vulkan;
class VK_engine;
class VK_imgui;


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
