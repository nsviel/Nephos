#pragma once

#include <glm/glm.hpp>

namespace vk{class Structure;}
namespace vk::gui{class Imgui;}
namespace vk::image{class Texture;}
namespace vk::image{class Screenshot;}
namespace vk::window{class GLFW;}
namespace vk::data{class Data;}


namespace vk{

class Interface
{
public:
  //Constructor / Destructor
  Interface(vk::Structure* vk_struct);
  ~Interface();

public:
  //Main function
  void set_mouse_pose(glm::vec2 pos);
  glm::vec2 get_mouse_pose();
  glm::vec2 get_dimension();

private:
  vk::gui::Imgui* vk_imgui;
  vk::image::Texture* vk_texture;
  vk::image::Screenshot* vk_screenshot;
  vk::window::GLFW* vk_window;
  vk::data::Data* vk_data;
};

}
