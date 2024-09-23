#pragma once

#include <imgui/core/imgui.h>
#include <glm/glm.hpp>
#include <memory>

namespace vk{class Structure;}
namespace vk::gui{class Imgui;}
namespace vk::image{class Screenshot;}
namespace vk::window{class Window;}


namespace vk{

class Window
{
public:
  //Constructor / Destructor
  Window(vk::Structure* vk_struct);
  ~Window();

public:
  //Main function
  glm::vec2 get_mouse_pose();
  glm::vec2 get_dimension();
  void set_mouse_pose(glm::vec2 pos);
  void make_screenshot();
  void set_mat_view(glm::mat4 mat);
  void set_mat_projection(glm::mat4 mat);

private:
  vk::Structure* vk_struct;
  vk::gui::Imgui* vk_imgui;
  vk::image::Screenshot* vk_screenshot;
  vk::window::Window* vk_window;
};

}
