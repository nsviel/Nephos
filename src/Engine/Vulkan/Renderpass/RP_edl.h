#ifndef VK_EDL_RENDERPASS_H
#define VK_EDL_RENDERPASS_H

#include <Vulkan/Struct/struct_renderpass.h>
#include <Vulkan/Struct/struct_pipeline.h>
#include <Shader/Shader.h>
#include <Specific/common.h>

class VK_engine;
class VK_struct;
class VK_pipeline;
class VK_subpass;
class VK_viewport;


class RP_edl
{
public:
  //Constructor / Destructor
  RP_edl(VK_engine* vk_engine);
  ~RP_edl();

public:
  //Main functions
  void init_renderpass(Struct_renderpass* renderpass);

  //Pipeline
  Struct_pipeline* create_pipeline_edl(Struct_renderpass* renderpass);
  void recreate_pipeline_edl();

private:
  VK_engine* vk_engine;
  VK_struct* vk_struct;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;
  VK_viewport* vk_viewport;
};

#endif
