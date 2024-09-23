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

  auto it = vk_struct->core.data.map_vk_object.find(data.UID);
  if(it == vk_struct->core.data.map_vk_object.end()) return nullptr;

  //---------------------------
  return it->second;
}
std::shared_ptr<vk::structure::Texture> Function::retrieve_vk_texture(vk::structure::Object& vk_object, std::string name){
  //---------------------------

  auto it = vk_object.map_texture.find(name);
  if(it == vk_object.map_texture.end()) return nullptr;

  //---------------------------
  return it->second;
}

}
