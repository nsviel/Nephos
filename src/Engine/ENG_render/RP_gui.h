#ifndef RP_UI_H
#define RP_UI_H

#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_pipeline.h>
#include <ELE_specific/common.h>

class ENG_shader;
class Engine;
class Struct_vulkan;
class VK_pipeline;
class VK_viewport;


class RP_gui
{
public:
  //Constructor / Destructor
  RP_gui(Engine* engine);
  ~RP_gui();

public:
  //Init functions
  Struct_renderpass* init_renderpass();
  void create_subpass(Struct_renderpass* renderpass);

  //Draw function
  void draw_gui(Struct_subpass* subpass);

private:
  ENG_shader* eng_shader;
  Struct_vulkan* struct_vulkan;
  VK_pipeline* vk_pipeline;
  VK_viewport* vk_viewport;
};

#endif
