#ifndef GUI_RENDERPASS_H
#define GUI_RENDERPASS_H

#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_pipeline.h>
#include <ELE_specific/common.h>

class Vulkan;
class VK_engine;
class VK_imgui;


class GUI_renderpass
{
public:
  //Constructor / Destructor
  GUI_renderpass(Vulkan* gui_vulkan);
  ~GUI_renderpass();

public:
  //Main functions
  void init_renderpass();
  void create_subpass(Struct_renderpass* renderpass);

  //Draw function
  void draw(Struct_subpass* subpass);

private:
  VK_imgui* vk_imgui;
  VK_engine* vk_engine;
};

#endif
