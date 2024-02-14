#pragma once

#include <Utility/Specific/common.h>
#include <imgui/implot/implot.h>

namespace vk::instance{class Pool;}
namespace vk::command{class Command;}
namespace vk::command{class Command_buffer;}
namespace vk::presentation{class Surface;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Command_buffer;}
namespace vk::main{class Texture;}


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
  void draw(vk::structure::Command_buffer* command_buffer);
  void clean();
  void render();
  void new_frame();

  ImTextureID create_imgui_texture(int UID);
  ImTextureID query_engine_texture();
  void create_context();
  bool check_window_resize();

  //Font
  void select_font();
  void load_font();

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::structure::Command_buffer* command_buffer;
  vk::command::Command* vk_command;
  vk::command::Command_buffer* vk_command_buffer;
  vk::instance::Pool* vk_pool;
  vk::presentation::Surface* vk_surface;
  vk::main::Texture* vk_texture;
};

}
