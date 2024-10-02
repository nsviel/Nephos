#pragma once

#include <imgui/core/imgui.h>
#include <glm/glm.hpp>
#include <memory>

namespace vk{class Structure;}
namespace vk::texture{class Image;}
namespace vk::texture{class Depth;}
namespace vk::texture{class Storage;}
namespace utl::base{class Image;}
namespace utl::base{class Depth;}
namespace utl::base{class Storage;}
namespace utl::base{class Data;}


namespace vk::interface{

class Texture
{
public:
  //Constructor / Destructor
  Texture(vk::Structure* vk_struct);
  ~Texture();

public:
  //Image
  void insert_image(utl::base::Data& data, std::shared_ptr<utl::base::Image> utl_image);
  void insert_image(std::shared_ptr<utl::base::Image> image);
  void update_image(std::shared_ptr<utl::base::Image> image);

  //Depth
  void insert_depth(utl::base::Data& data, std::shared_ptr<utl::base::Depth> depth);
  void update_depth(std::shared_ptr<utl::base::Depth> depth);

  //Storage
  void insert_storage(utl::base::Data& data, std::shared_ptr<utl::base::Storage> storage);
  void update_storage(std::shared_ptr<utl::base::Storage> storage);

private:
  vk::Structure* vk_struct;
  vk::texture::Image* vk_tex_image;
  vk::texture::Depth* vk_tex_depth;
  vk::texture::Storage* vk_tex_storage;
};

}
