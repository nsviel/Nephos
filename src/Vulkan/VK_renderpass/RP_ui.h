#ifndef RP_UI_H
#define RP_UI_H

#include <VK_struct/struct_renderpass.h>
#include <VK_struct/struct_pipeline.h>
#include <ELE_specific/common.h>

class VK_engine;
class struct_vulkan;
class VK_pipeline;
class VK_subpass;
class VK_viewport;


class RP_ui
{
public:
  //Constructor / Destructor
  RP_ui(VK_engine* vk_engine);
  ~RP_ui();

public:
  //Main functions
  void init_renderpass(Struct_renderpass* renderpass);

  //Pipeline
  void create_pipeline_canvas(Struct_renderpass* renderpass);

private:
  VK_engine* vk_engine;
  struct_vulkan* vk_struct;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;
  VK_viewport* vk_viewport;
};

#endif
