#include "Function.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::data{

//Constructor / Destructor
Function::Function(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Function::~Function(){}

//Main function
std::shared_ptr<vk::structure::Object> Function::retrieve_vk_object(utl::base::Data& data){
  //---------------------------

  auto it = vk_struct->core.data.map_object.find(data.UID);
  if(it == vk_struct->core.data.map_object.end()) return nullptr;

  //---------------------------
  return it->second;
}
std::shared_ptr<vk::structure::Texture> Function::retrieve_vk_texture(utl::media::Image& image){
  //---------------------------

  //Search in all vk objects
  for(auto& [name, vk_object] : vk_struct->core.data.map_object){
    auto texture = retrieve_vk_texture(*vk_object, image.name);
    if(texture) return texture;
  }

  //Search in all engine textures
  for(auto& texture : vk_struct->core.data.list_vk_texture){
    if(texture->image->UID == image.UID) return texture;
  }

  //---------------------------
  return nullptr;
}
std::shared_ptr<vk::structure::Texture> Function::retrieve_vk_texture(vk::structure::Object& vk_object, std::string name){
  //---------------------------

  auto it = vk_object.map_texture.find(name);
  if(it == vk_object.map_texture.end()) return nullptr;

  //---------------------------
  return it->second;
}

}
