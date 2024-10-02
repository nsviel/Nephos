#pragma once

#include <imgui/core/imgui.h>
#include <glm/glm.hpp>
#include <memory>

namespace vk{class Structure;}
namespace vk::texture{class Data;}
namespace utl::base{class Image;}
namespace utl::base{class Data;}


namespace vk::interface{

class Texture
{
public:
  //Constructor / Destructor
  Texture(vk::Structure* vk_struct);
  ~Texture();

public:
  //Main function
  void insert_image(utl::base::Data& data, std::shared_ptr<utl::base::Image> utl_image);
  void insert_image(std::shared_ptr<utl::base::Image> image);
  void update_image(std::shared_ptr<utl::base::Image> image);

private:
  vk::Structure* vk_struct;
  vk::texture::Data* vk_texture;
};

}
