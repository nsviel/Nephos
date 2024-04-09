#pragma once

#include <Utility/Specific/Common.h>
#include <imgui/implot/implot.h>

namespace vk::instance{class Pool;}
namespace vk::command{class Command_buffer;}
namespace vk::command{class Allocator;}
namespace vk::presentation{class Surface;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Command_buffer;}
namespace vk::image{class Texture;}


namespace vk::gui{

class Imgui
{
public:
  //Constructor / Destructor
  Imgui(vk::structure::Vulkan* vk_struct);
  ~Imgui();

public:
  //Main functions
  void init();
  void draw(vk::structure::Command_buffer* command_buffer);
  void clean();
  void render();
  void new_frame();

  //Context
  void create_context();
  bool check_window_resize();

  //Texture
  void load_texture(utl::media::Image* utl_image);
  ImTextureID create_imgui_texture(int UID);
  ImTextureID query_engine_texture();

  //Font
  void select_font();
  void load_font();

private:
  vk::structure::Vulkan* vk_struct;
  vk::structure::Command_buffer* command_buffer;
  vk::command::Allocator* vk_allocator;
  vk::command::Command_buffer* vk_command_buffer;
  vk::instance::Pool* vk_pool;
  vk::presentation::Surface* vk_surface;
  vk::image::Texture* vk_texture;
};

}
