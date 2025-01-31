#include "Texture.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::texture{

//Constructor / Destructor
Texture::Texture(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);
  this->vk_format = new vk::image::Format(vk_struct);
  this->vk_texture = new vk::texture::Ressource(vk_struct);

  //---------------------------
}
Texture::~Texture(){}

//Main function
void Texture::init(){
  //---------------------------

  utl::base::Image image;
  image.name = "blank";
  image.width = 100;
  image.height = 100;
  image.size = image.width * image.height * 4;
  image.format = "RGBA8";

  image.data.resize(image.width * image.height * 4);
  for (size_t i = 0; i < image.data.size(); i += 4) {
    image.data[i] = 255;     // Red
    image.data[i + 1] = 255; // Green
    image.data[i + 2] = 255; // Blue
    image.data[i + 3] = 255; // Alpha
  }

  //Create blank image
  vk::structure::Texture& blank = vk_struct->core.image.blank;
  blank.image = std::make_shared<utl::base::Image>(image);
  blank.surface.width = 100;
  blank.surface.height = 100;
  blank.surface.format = VK_FORMAT_R8G8B8A8_UNORM;
  blank.surface.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  blank.surface.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
  blank.surface.layout = VK_IMAGE_LAYOUT_GENERAL;

  vk_texture->create_texture(blank);

  //---------------------------
}
void Texture::clean(){
  //---------------------------

  //Create blank image
  vk::structure::Texture& blank = vk_struct->core.image.blank;
  vk_texture->clean_texture(blank);

  //---------------------------
}

}
