#pragma once

#include <Utility/Specific/common.h>
#include <imgui/implot/implot.h>

class VK_engine;
namespace vk::instance{class Pool;}
namespace vk::command{class Submit;}
namespace vk::command{class Command;}
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
  vk::command::Submit* vk_submit;
  vk::command::Command* vk_command;
  vk::instance::Pool* vk_pool;
  VK_surface* vk_surface;
};
