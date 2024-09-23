#include "UID.h"

#include <Vulkan/Namespace.h>


namespace vk::instance{

//Constructor / Destructor
UID::UID(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
UID::~UID(){}

//Main function
int UID::query_free_UID(){
  //---------------------------



  //---------------------------
  return vk_struct->interface.state.UID++;
}

}
