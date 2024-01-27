#pragma once

#include <Utility/Specific/common.h>
#include <imgui/implot/implot.h>

namespace vk::main{class Engine;}
namespace vk::instance{class Pool;}
namespace vk::command{class Submit;}
namespace vk::command{class Command;}
namespace vk::presentation{class VK_surface;}
namespace vk::structure{class Vulkan;}


namespace vk::main{

class Imgui
{
public:
  //Constructor / Destructor
  Imgui(vk::structure::Vulkan* struct_vulkan);
  ~Imgui();

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
  vk::main::Engine* vk_engine;
  vk::command::Submit* vk_submit;
  vk::command::Command* vk_command;
  vk::instance::Pool* vk_pool;
  vk::presentation::VK_surface* vk_surface;
};

}
