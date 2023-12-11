#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>


class VK_engine;
class VK_pool;
class VK_submit;
class VK_command;
class VK_surface;


class VK_imgui
{
public:
  //Constructor / Destructor
  VK_imgui(vk::structure::Vulkan* struct_vulkan);
  ~VK_imgui();

public:
  //Main functions
  void init();
  void draw(VkCommandBuffer& command_buffer);
  void load_font();
  void clean();

  ImTextureID rendered_texture();
  bool check_window_resize();

private:
  vk::structure::Vulkan* struct_vulkan;
  VK_engine* vk_engine;
  VK_submit* vk_submit;
  VK_command* vk_command;
  VK_pool* vk_pool;
  VK_surface* vk_surface;
};
