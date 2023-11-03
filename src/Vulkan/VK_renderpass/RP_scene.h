#ifndef RP_SCENE_H
#define RP_SCENE_H

#include <VK_struct/struct_renderpass.h>
#include <VK_struct/struct_pipeline.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_pipeline;
class VK_subpass;
class VK_viewport;


class RP_scene
{
public:
  //Constructor / Destructor
  RP_scene(VK_engine* vk_engine);
  ~RP_scene();

public:
  //Main functions
  void init_renderpass(Struct_renderpass* renderpass);

  //Pipeline
  void create_pipeline_point(Struct_renderpass* renderpass);
  void create_pipeline_line(Struct_renderpass* renderpass);

private:
  VK_engine* vk_engine;
  Struct_vulkan* vk_struct;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;
  VK_viewport* vk_viewport;
};

#endif
