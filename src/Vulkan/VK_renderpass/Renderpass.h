#pragma once

#include <VK_struct/Struct_vk_renderpass.h>
#include <VK_struct/Struct_vk_pipeline.h>
#include <UTL_specific/common.h>
#include <Vulkan_namespace.h>

class Struct_vulkan;
class VK_pipeline;
class VK_framebuffer;
class VK_command;


namespace vk{
class Subpass;


class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(Struct_vulkan* struct_vulkan);
  ~Renderpass();

public:
  //Main functions
  void init_renderpass();
  void clean_renderpass();

  //Subfunction
  void create_renderpass_struct(Struct_vk_renderpass* renderpass);
  void create_renderpass_obj(Struct_vk_renderpass* renderpass);
  void clean_renderpass_struct(Struct_vk_renderpass* renderpass);

private:
  Struct_vulkan* struct_vulkan;
  VK_pipeline* vk_pipeline;
  vk::Subpass* vk_subpass;
  VK_framebuffer* vk_framebuffer;
  VK_command* vk_command;
};

}
