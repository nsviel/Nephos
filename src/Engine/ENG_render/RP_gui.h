#ifndef RP_UI_H
#define RP_UI_H

#include <VK_struct/Struct_vk_renderpass.h>
#include <VK_struct/Struct_vk_pipeline.h>
#include <UTL_specific/common.h>

class Engine;
class VK_engine;
class VK_imgui;


class RP_gui
{
public:
  //Constructor / Destructor
  RP_gui(Engine* engine);
  ~RP_gui();

public:
  //Main functions
  void init_renderpass();
  void create_subpass(Struct_vk_renderpass* renderpass);

  void draw(Struct_vk_subpass* subpass);

private:
  VK_engine* vk_engine;
  VK_imgui* vk_imgui;
};

#endif
