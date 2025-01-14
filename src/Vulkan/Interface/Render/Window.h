#pragma once

#include <imgui/core/imgui.h>
#include <glm/glm.hpp>
#include <memory>

namespace vk{class Structure;}
namespace vk::image{class Screenshot;}
namespace vk::window{class Window;}


namespace vk::interface{

class Window
{
public:
  //Constructor / Destructor
  Window(vk::Structure* vk_struct);
  ~Window();

public:
  //Main function
  glm::vec2 get_mouse_pose();
  glm::vec2 get_window_dimension();
  void set_mouse_pose(glm::vec2 pos);
  void make_screenshot_color();
  void make_screenshot_depth();
  void set_mat_view(glm::mat4 mat);
  void set_mat_projection(glm::mat4 mat);
  bool is_running();

private:
  vk::Structure* vk_struct;
  vk::image::Screenshot* vk_screenshot;
  vk::window::Window* vk_window;
};

}
