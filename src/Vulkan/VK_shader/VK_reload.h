#pragma once

#include <VK_struct/Namespace.h>
#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>


class VK_pipeline;


class VK_reload
{
public:
  //Constructor / Destructor
  VK_reload(vk::structure::Struct_vulkan* struct_vulkan);
  ~VK_reload();

public:
  //Main function
  void hot_shader_reload(string shader_1, string shader_2);
  void recreate_pipeline(vk::structure::Renderpass* renderpass, vk::structure::Pipeline* pipeline);

private:
  vk::structure::Struct_vulkan* struct_vulkan;
  VK_pipeline* vk_pipeline;
};
