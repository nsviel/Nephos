#include "Data.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::texture{

//Constructor / Destructor
Data::Data(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_ressource = new vk::texture::Ressource(vk_struct);

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::insert_texture(utl::base::Data& data, std::shared_ptr<utl::media::Image> image){
  //---------------------------

  //Check image integrity
  if(!image) return;
  if(image->format == "") return;
  if(image->size == 0) return;
  if(image->width == 0) return;
  if(image->height == 0) return;

  //Retrieve data vk object
  auto it_object = vk_struct->core.data.map_vk_object.find(data.UID);
  if(it_object == vk_struct->core.data.map_vk_object.end()) return;
  auto vk_object = it_object->second;

  //Check if image already inserted
  auto it_tex = vk_object->map_texture.find(image->name);
  if(it_tex != vk_object->map_texture.end()) return;

  //Create texture from image
  this->create_texture(*vk_object, image);

  //---------------------------
}

//Subfunction
void Data::create_texture(vk::structure::Object& vk_object, std::shared_ptr<utl::media::Image> image){
  //---------------------------

  auto texture = std::make_shared<vk::structure::Texture>();
  texture->image = image;
  vk_ressource->create_texture(texture);
  vk_object.map_texture[image->name] = texture;

  //---------------------------
}
void Data::clean_texture(vk::structure::Object& vk_object){
  //---------------------------

  for(auto& [name, texture] : vk_object.map_texture){
    vk_ressource->clean_texture(texture);
  }

  //---------------------------
}

}
