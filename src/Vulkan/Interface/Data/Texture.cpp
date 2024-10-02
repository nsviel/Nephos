#include "Texture.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::interface{

//Constructor / Destructor
Texture::Texture(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_texture = new vk::texture::Data(vk_struct);

  //---------------------------
}
Texture::~Texture(){}

//Main function
void Texture::insert_image(utl::base::Data& data, std::shared_ptr<utl::base::Image> image){
  vk_texture->insert_texture(data, image);
}
void Texture::insert_image(std::shared_ptr<utl::base::Image> image){
  vk_texture->insert_texture(image);
}
void Texture::update_image(std::shared_ptr<utl::base::Image> image){
  vk_texture->update_texture(image);
}

}
