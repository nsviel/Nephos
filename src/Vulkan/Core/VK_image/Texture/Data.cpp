#include "Data.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::texture{

//Constructor / Destructor
Data::Data(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_ressource = new vk::texture::Ressource(vk_struct);
  this->vk_data = new vk::data::Function(vk_struct);

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::insert_texture(utl::base::Data& data, std::shared_ptr<utl::media::Image> image){say("---");
  if(!check_image(image)) return;
  //---------------------------

  //Retrieve data vk object
  auto vk_object = vk_data->retrieve_vk_object(data);
  if(!vk_object) return;

  //Check if image already inserted
  auto vk_texture = vk_data->retrieve_vk_texture(*vk_object, image->name);
  if(vk_texture) return;

  //Create texture from image and insert
  auto texture = std::make_shared<vk::structure::Texture>();
  texture->image = image;
  vk_ressource->create_texture(*texture);
  vk_object->map_texture[image->name] = texture;

  //---------------------------
}
void Data::insert_texture(std::shared_ptr<utl::media::Image> image){
  if(!check_image(image)) return;
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
void Data::update_texture(std::shared_ptr<utl::media::Image> image){
  if(!check_image(image)) return;
  //---------------------------

  //Retrieve data vk object
  auto texture = vk_data->retrieve_vk_texture(*image);
  if(!texture) return;

  //Create texture from image
  vk_ressource->update_texture(*texture);

  //---------------------------
}

//Subfunction
void Data::create_texture(vk::structure::Object& vk_object, std::shared_ptr<utl::media::Image> image){
  //---------------------------

  auto texture = std::make_shared<vk::structure::Texture>();
  texture->image = image;
  vk_ressource->create_texture(*texture);

  //---------------------------
}
void Data::clean_texture(vk::structure::Object& vk_object){
  //---------------------------

  for(auto& [name, texture] : vk_object.map_texture){
    vk_ressource->clean_texture(*texture);
  }

  //---------------------------
}
bool Data::check_image(std::shared_ptr<utl::media::Image> image){
  //---------------------------

  if(!image) return false;
  if(image->format == "") return false;
  if(image->size == 0) return false;
  if(image->width == 0) return false;
  if(image->height == 0) return false;

  //---------------------------
  return true;
}

}
