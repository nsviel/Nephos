#include "Image.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::texture{

//Constructor / Destructor
Image::Image(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_ressource = new vk::texture::Ressource(vk_struct);
  this->vk_retriever = new vk::data::Retriever(vk_struct);

  //---------------------------
}
Image::~Image(){}

//Main function
void Image::insert_image(utl::base::Data& data, std::shared_ptr<utl::base::Image> image){
  //---------------------------

  //Retrieve data vk object
  auto vk_object = vk_retriever->retrieve_vk_object(data);
  if(!vk_object) return;

  //Insert in vk object
  this->insert_image(*vk_object, image);

  //---------------------------
}
void Image::insert_image(vk::structure::Object& vk_object, std::shared_ptr<utl::base::Image> image){
  if(!vk_ressource->check_image(image)) return;
  //---------------------------

  //Check if image already inserted
  auto vk_texture = vk_retriever->retrieve_vk_texture(vk_object, image->name);
  if(vk_texture) return;

  //Create texture from image and insert
  auto texture = std::make_shared<vk::structure::Texture>();
  texture->image = image;
  vk_ressource->create_texture(*texture);
  vk_object.map_texture[image->name] = texture;

  //---------------------------
}
void Image::insert_image(std::shared_ptr<utl::base::Image> image){
  if(!vk_ressource->check_image(image)) return;
  //---------------------------

  //Check if image already inserted
  for(auto& texture : vk_struct->core.data.list_vk_texture){
    if(texture->image->UID == image->UID) return;
  }

  //Create texture from image
  auto texture = std::make_shared<vk::structure::Texture>();
  texture->image = image;
  vk_ressource->create_texture(*texture);
  vk_struct->core.data.list_vk_texture.push_back(texture);

  //---------------------------
}
void Image::update_texture(std::shared_ptr<utl::base::Image> image){
  if(!vk_ressource->check_image(image)) return;
  //---------------------------

  //Retrieve data vk object
  auto texture = vk_retriever->retrieve_vk_texture(*image);
  if(!texture) return;

  //Create texture from image
  vk_ressource->update_texture(*texture);

  //---------------------------
}

//Subfunction
void Image::clean_texture(vk::structure::Object& vk_object){
  //---------------------------

  for(auto& [name, texture] : vk_object.map_texture){
    vk_ressource->clean_texture(*texture);
  }

  //---------------------------
}

}
