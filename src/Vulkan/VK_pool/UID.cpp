#include "UID.h"

#include <Vulkan/Namespace.h>


namespace vk::instance{

//Constructor / Destructor
UID::UID(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
UID::~UID(){}

//Main functions
int UID::query_free_UID(){
  //---------------------------



  //---------------------------
  return struct_vulkan->UID++;
}

}
