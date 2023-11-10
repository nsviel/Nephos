#ifndef VK_RELOAD_H
#define VK_RELOAD_H

#include <VK_struct/Struct_pipeline.h>
#include <VK_struct/Struct_renderpass.h>
#include <ELE_specific/common.h>

class VK_engine;
class VK_pipeline;
class Struct_vulkan;
class VK_renderpass;


class VK_reload
{
public:
  //Constructor / Destructor
  VK_reload(Struct_vulkan* struct_vulkan);
  ~VK_reload();

public:
  //Main function
  void hot_shader_reload(string shader_1, string shader_2);
  void recreate_pipeline(Struct_renderpass* renderpass, Struct_pipeline* pipeline);

private:
  VK_pipeline* vk_pipeline;
  Struct_vulkan* struct_vulkan;
  VK_renderpass* vk_renderpass;
};

#endif
