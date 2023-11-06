#ifndef RP_UI_H
#define RP_UI_H

#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_pipeline.h>
#include <ELE_specific/common.h>

class ENG_shader;
class Engine;
class Struct_vulkan;
class VK_engine;
class VK_pipeline;
class VK_command;
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
  void create_pipeline_canvas(Struct_renderpass* renderpass);

  //Draw function
  void draw_gui(Struct_renderpass* renderpass);

private:
  ENG_shader* eng_shader;
  Struct_vulkan* struct_vulkan;
  VK_engine* vk_engine;
  VK_pipeline* vk_pipeline;
  VK_command* vk_command;
  VK_viewport* vk_viewport;
};

#endif
