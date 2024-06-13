#include "Manager.h"

#include <Vulkan/Namespace.h>


namespace vk::queue{

//Constructor / Destructor
Manager::Manager(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::init(){
  //---------------------------

  vk_struct->queue.transfer = new vk::queue::Transfer(vk_struct);
  vk_struct->queue.graphics = new vk::queue::Graphics(vk_struct);
  vk_struct->queue.presentation = new vk::queue::Presentation(vk_struct);

  //---------------------------
}
void Manager::clean(){
  //---------------------------

  vk_struct->queue.transfer->stop_thread();
  vk_struct->queue.graphics->stop_thread();

  //---------------------------
}

}
