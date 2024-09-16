#pragma once

#include <imgui/core/imgui.h>
#include <glm/glm.hpp>
#include <memory>

namespace vk{class Structure;}
namespace vk::gui{class Imgui;}
namespace vk::image{class Texture;}
namespace vk::image{class Screenshot;}
namespace vk::window{class GLFW;}
namespace vk::data{class Data;}
namespace utl::media{class Image;}


namespace vk{

class Interface
{
public:
  //Constructor / Destructor
  Interface(vk::Structure* vk_struct);
  ~Interface();

public:
  //Main function
  void insert_data(std::shared_ptr<utl::base::Data> data, std::shared_ptr<utl::base::Pose> pose);
  void remove_data(utl::base::Data& data);
  void load_texture(std::shared_ptr<utl::media::Image> utl_image);
  void set_mouse_pose(glm::vec2 pos);
  glm::vec2 get_mouse_pose();
  glm::vec2 get_dimension();
  ImTextureID query_engine_texture();
  void insert_texture(std::shared_ptr<utl::media::Image> utl_image);
  void make_screenshot();

private:
  vk::gui::Imgui* vk_imgui;
  vk::image::Texture* vk_texture;
  vk::image::Screenshot* vk_screenshot;
  vk::window::GLFW* vk_window;
  vk::data::Data* vk_data;
};

}
