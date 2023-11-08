#ifndef VK_RENDERPASS_H
#define VK_RENDERPASS_H

#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_pipeline.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_color;
class VK_pipeline;
class VK_subpass;
class VK_frame;
class VK_framebuffer;


class VK_renderpass
{
public:
  //Constructor / Destructor
  VK_renderpass(VK_engine* vk_engine);
  ~VK_renderpass();

public:
  //Main functions
  void init_renderpass();
  void clean_renderpass();

  //Subfunction
  void create_renderpass_struct(Struct_renderpass* renderpass);
  void create_renderpass_obj(Struct_renderpass* renderpass);
  void clean_renderpass_struct(Struct_renderpass* renderpass);

private:
  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;
  VK_color* vk_color;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;
  VK_frame* vk_frame;
  VK_framebuffer* vk_framebuffer;
};

#endif
