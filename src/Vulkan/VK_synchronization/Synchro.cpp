#include "Synchro.h"

#include <Vulkan/Namespace.h>


namespace vk::synchro{

//Constructor / Destructor
Synchro::Synchro(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
Synchro::~Synchro(){}

//Main function
void Synchro::wait_idle(){
  //---------------------------

//say(struct_vulkan->queue.transfer->is_queue_idle());
  struct_vulkan->queue.standby = true;
  struct_vulkan->queue.transfer->wait_for_idle();
  vkDeviceWaitIdle(struct_vulkan->device.handle);

  //---------------------------
}
void Synchro::end_idle(){
  //---------------------------

  struct_vulkan->queue.standby = false;

  //---------------------------
}

}
