#include "Manager.h"

#include <Vulkan/Namespace.h>


namespace vk::queue{

//Constructor / Destructor
Manager::Manager(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
Manager::~Manager(){}

//Main functions
void Manager::init(){
  //---------------------------

  struct_vulkan->transfer = new vk::queue::Transfer(struct_vulkan);

  //---------------------------
}

}
