#pragma once

#include <imgui/core/imgui.h>
#include <glm/glm.hpp>
#include <memory>

namespace vk{class Structure;}
namespace vk::gui{class Render;}
namespace vk::texture{class Data;}
namespace vk::data{class Data;}
namespace utl::media{class Image;}
namespace utl::base{class Data;}
namespace utl::base{class Pose;}


namespace vk::interface{

class Data
{
public:
  //Constructor / Destructor
  Data(vk::Structure* vk_struct);
  ~Data();

public:
  //Main function
  ImTextureID query_render_texture();
  void draw_render_texture(glm::vec2 dimension);
  void insert_data(std::shared_ptr<utl::base::Data> data, std::shared_ptr<utl::base::Pose> pose);
  void remove_data(utl::base::Data& data);
  void insert_texture(utl::base::Data& data, std::shared_ptr<utl::media::Image> utl_image);
  void draw_texture(utl::base::Data& data, std::shared_ptr<utl::media::Image> image);

private:
  vk::Structure* vk_struct;
  vk::texture::Data* vk_texture;
  vk::data::Data* vk_data;
  vk::gui::Render* vk_render;
};

}
