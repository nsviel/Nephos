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
namespace utl::base{class Data;}
namespace utl::base{class Pose;}


namespace vk{

class Interface
{
public:
  //Constructor / Destructor
  Interface(vk::Structure* vk_struct);
  ~Interface();

public:
  //Data function
  ImTextureID query_engine_texture();
  void insert_data(std::shared_ptr<utl::base::Data> data, std::shared_ptr<utl::base::Pose> pose);
  void remove_data(utl::base::Data& data);
  void insert_texture(std::shared_ptr<utl::media::Image> utl_image);
  void load_texture(std::shared_ptr<utl::media::Image> utl_image);

  //Window function
  glm::vec2 get_mouse_pose();
  glm::vec2 get_dimension();
  void set_mouse_pose(glm::vec2 pos);
  void make_screenshot();

private:
  vk::gui::Imgui* vk_imgui;
  vk::image::Texture* vk_texture;
  vk::image::Screenshot* vk_screenshot;
  vk::window::GLFW* vk_window;
  vk::data::Data* vk_data;
};

}
