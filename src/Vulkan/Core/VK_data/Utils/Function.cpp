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

  auto it_object = vk_struct->core.data.map_vk_object.find(data.UID);
  if(it_object == vk_struct->core.data.map_vk_object.end()) return nullptr;

  //---------------------------
  return it_object->second;
}

}
