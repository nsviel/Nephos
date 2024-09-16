#include "Manager.h"

#include <Vulkan/Namespace.h>


namespace vk::queue{

//Constructor / Destructor
Manager::Manager(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::init(){
  //---------------------------

  vk_struct->core.queue.transfer = new vk::queue::transfer::Thread(vk_struct);
  vk_struct->core.queue.graphics = new vk::queue::graphics::Thread(vk_struct);
  vk_struct->core.queue.presentation = new vk::queue::presentation::Thread(vk_struct);

  //---------------------------
}
void Manager::clean(){
  //---------------------------

  vk_struct->core.queue.transfer->stop_thread();
  vk_struct->core.queue.graphics->stop_thread();

  //---------------------------
}

}
