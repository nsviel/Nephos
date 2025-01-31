#include "Image.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::image{

//Constructor / Destructor
Image::Image(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);
  this->vk_format = new vk::image::Format(vk_struct);
  this->vk_image = new vk::image::Ressource(vk_struct);

  //---------------------------
}
Image::~Image(){}

//Main function
void Image::init(){
  //---------------------------

  //Create blank image
  vk::structure::Image& blank = vk_struct->core.image.blank;
  blank.width = 100;
  blank.height = 100;
  blank.size = 100 * 100 * 4;
  vk_image->create_image(blank);

  //---------------------------
}
void Image::clean(){
  //---------------------------

  //Create blank image
  vk::structure::Image& blank = vk_struct->core.image.blank;
  vk_image->clean_image(blank);

  //---------------------------
}

}
