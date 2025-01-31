#include "Texture.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::image{

//Constructor / Destructor
Texture::Texture(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);
  this->vk_format = new vk::image::Format(vk_struct);
  this->vk_image = new vk::image::Ressource(vk_struct);

  //---------------------------
}
Texture::~Texture(){}

//Main function
void Texture::init(){
  //---------------------------

  //Create blank image
  vk::structure::Image& blank = vk_struct->core.image.blank;
  blank.name = "blank";
  blank.width = 100;
  blank.height = 100;
  blank.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  blank.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
  blank.format = VK_FORMAT_R8G8B8A8_UNORM;
  blank.layout = VK_IMAGE_LAYOUT_GENERAL;
  vk_image->create_image(blank);

  //---------------------------
}
void Texture::clean(){
  //---------------------------

  //Create blank image
  vk::structure::Image& blank = vk_struct->core.image.blank;
  vk_image->clean_image(blank);

  //---------------------------
}

}
