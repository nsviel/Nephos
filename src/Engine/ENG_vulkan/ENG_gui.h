#ifndef RP_UI_H
#define RP_UI_H

#include <VK_struct/struct_renderpass.h>
#include <VK_struct/struct_pipeline.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_pipeline;
class VK_subpass;
class VK_viewport;


class ENG_gui
{
public:
  //Constructor / Destructor
  ENG_gui(VK_engine* vk_engine);
  ~ENG_gui();

public:
  //Main functions
  Struct_renderpass* init_renderpass();

  //Pipeline
  void create_pipeline_canvas(Struct_renderpass* renderpass);

private:
  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;
  VK_viewport* vk_viewport;
};

#endif
