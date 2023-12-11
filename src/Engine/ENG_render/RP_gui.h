#pragma once

#include <VK_struct/Namespace.h>
#include <VK_struct/Pipeline.h>
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
  void create_subpass(vk::structure::Renderpass* renderpass);

  void draw(vk::structure::Subpass* subpass);

private:
  VK_engine* vk_engine;
  VK_imgui* vk_imgui;
};
