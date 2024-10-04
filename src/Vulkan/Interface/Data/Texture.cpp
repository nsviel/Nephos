#include "Texture.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::interface{

//Constructor / Destructor
Texture::Texture(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_tex_image = new vk::texture::Image(vk_struct);
  this->vk_tex_storage = new vk::texture::Storage(vk_struct);
  this->vk_tex_depth = new vk::texture::Depth(vk_struct);

  //---------------------------
}
Texture::~Texture(){}

//Image
void Texture::insert_image(utl::base::Data& data, std::shared_ptr<utl::base::Image> image){
  vk_tex_image->insert_image(data, image);
}
void Texture::insert_image(std::shared_ptr<utl::base::Image> image){
  vk_tex_image->insert_image(image);
}
void Texture::update_image(utl::base::Data& data, std::shared_ptr<utl::base::Image> image){
  vk_tex_image->update_image(data, image);
}

//Depth
void Texture::insert_depth(utl::base::Data& data, std::shared_ptr<utl::base::Depth> depth){
  vk_tex_depth->insert_depth(data, depth);
}
void Texture::update_depth(utl::base::Data& data, std::shared_ptr<utl::base::Depth> depth){
  vk_tex_depth->update_depth(data, depth);
}

//Storage
void Texture::insert_storage(utl::base::Data& data, std::shared_ptr<utl::base::Storage> storage){
  vk_tex_storage->insert_storage(data, storage);
}
void Texture::update_storage(utl::base::Data& data, std::shared_ptr<utl::base::Storage> storage){
  vk_tex_storage->update_storage(data, storage);
}


}
