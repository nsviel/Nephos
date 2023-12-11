#pragma once

#include <VK_struct/Struct_vk_pipeline.h>
#include <VK_struct/Struct_vk_renderpass.h>
#include <UTL_specific/common.h>

class Struct_vulkan;
class VK_pipeline;


class VK_reload
{
public:
  //Constructor / Destructor
  VK_reload(Struct_vulkan* struct_vulkan);
  ~VK_reload();

public:
  //Main function
  void hot_shader_reload(string shader_1, string shader_2);
  void recreate_pipeline(Struct_vk_renderpass* renderpass, Struct_vk_pipeline* pipeline);

private:
  Struct_vulkan* struct_vulkan;
  VK_pipeline* vk_pipeline;
};
