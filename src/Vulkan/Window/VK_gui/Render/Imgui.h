#pragma once

#include <imgui/implot/implot.h>
#include <memory>

namespace vk::instance{class Pool;}
namespace vk::presentation{class Surface;}
namespace vk{class Structure;}
namespace vk::structure{class Command_buffer;}
namespace vk::gui{class Texture;}
namespace vk::gui{class Font;}
namespace vk::window{class Window;}
namespace vk::gui{class Docking;}
namespace utl::media{class Image;}


namespace vk::gui{

class Imgui
{
public:
  //Constructor / Destructor
  Imgui(vk::Structure* vk_struct);
  ~Imgui();

public:
  //Main function
  void init();
  void clean();
  void loop();

  //Context
  void create_context();
  void new_frame();
  void draw_frame(vk::structure::Command_buffer& command_buffer);
  void resize_event();
  void glfw_clean();
  void glfw_new_frame();

private:
  vk::Structure* vk_struct;
  vk::structure::Command_buffer* command_buffer;
  vk::instance::Pool* vk_pool;
  vk::presentation::Surface* vk_surface;
  vk::gui::Texture* vk_texture;
  vk::window::Window* vk_window;
  vk::gui::Font* vk_font;
  vk::gui::Docking* vk_docking;
};

}
