#ifndef RP_PSR_H
#define RP_PSR_H

#include <VK_struct/struct_renderpass.h>
#include <VK_struct/struct_pipeline.h>
#include <ENG_shader/Shader.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_pipeline;
class VK_subpass;
class VK_viewport;


class RP_psr
{
public:
  //Constructor / Destructor
  RP_psr(VK_engine* vk_engine);
  ~RP_psr();

public:
  //Main functions
  void init_renderpass(Struct_renderpass* renderpass);

  //Subpass
  void create_subpass_pyramid(Struct_renderpass* renderpass);

  //Pipeline
  void create_pipeline_canvas(Struct_renderpass* renderpass);
  void create_pipeline_pyramid(Struct_renderpass* renderpass);

private:
  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;
  VK_viewport* vk_viewport;
};

#endif
