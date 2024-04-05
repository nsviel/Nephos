#include "Synchro.h"

#include <Vulkan/Namespace.h>


namespace vk::synchro{

//Constructor / Destructor
Synchro::Synchro(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Synchro::~Synchro(){}

//Main function
void Synchro::wait_idle(){
  //---------------------------

  vk_struct->queue.standby = true;
  vk_struct->queue.transfer->wait_for_idle();
  vkDeviceWaitIdle(vk_struct->device.handle);

  //---------------------------
}
void Synchro::end_idle(){
  //---------------------------

  vk_struct->queue.standby = false;

  //---------------------------
}

}
