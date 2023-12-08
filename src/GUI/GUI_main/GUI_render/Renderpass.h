#pragma once

#include <VK_struct/Struct_vk_renderpass.h>
#include <VK_struct/Struct_vk_pipeline.h>
#include <UTL_specific/common.h>

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
  void create_subpass(Struct_vk_renderpass* renderpass);

  //Draw function
  void draw(Struct_vk_subpass* subpass);

private:
  VK_imgui* vk_imgui;
  VK_engine* vk_engine;
};

}
