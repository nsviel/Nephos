#ifndef VK_RENDERPASS_H
#define VK_RENDERPASS_H

#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_pipeline.h>
#include <ELE_specific/common.h>

class Struct_vulkan;
class VK_pipeline;
class VK_subpass;
class VK_framebuffer;


class VK_renderpass
{
public:
  //Constructor / Destructor
  VK_renderpass(Struct_vulkan* struct_vulkan);
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
  Struct_vulkan* struct_vulkan;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;
  VK_framebuffer* vk_framebuffer;
};

#endif
