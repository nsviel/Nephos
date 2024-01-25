#pragma once

#include <Utility/Specific/common.h>
#include <imgui/implot/implot.h>

class VK_engine;
class VK_pool;
namespace vk::command{class VK_submit;}
namespace vk::command{class VK_command;}
class VK_surface;
namespace vk::structure{class Vulkan;}


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
  vk::command::VK_submit* vk_submit;
  vk::command::VK_command* vk_command;
  VK_pool* vk_pool;
  VK_surface* vk_surface;
};
