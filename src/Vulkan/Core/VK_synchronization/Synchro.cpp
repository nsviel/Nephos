#include "Synchro.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::synchro{

//Constructor / Destructor
Synchro::Synchro(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Synchro::~Synchro(){}

//Main function
void Synchro::wait_idle(){
  //---------------------------
say("1-----");
  vk_struct->core.command.graphics->set_pause(true);
  vk_struct->core.command.transfer->set_pause(true);
  vkDeviceWaitIdle(vk_struct->core.device.handle);
sayHello();
  //---------------------------
}
void Synchro::wait_idle_and_pause(){
  if(vk_struct->core.device.handle == VK_NULL_HANDLE) std::cout<<"[error] vulkan device is vk null"<<std::endl;
  //---------------------------
say("2-----");
  //vk_struct->core.command.standby = true;sayHello();
  vk_struct->core.command.graphics->set_pause(true);sayHello();
  vk_struct->core.command.transfer->set_pause(true);sayHello();
//  vkDeviceWaitIdle(vk_struct->core.device.handle);
sayHello();
  //---------------------------
}
void Synchro::end_idle(){
  //---------------------------

  vk_struct->core.command.transfer->set_pause(false);
  vk_struct->core.command.graphics->set_pause(false);
  vk_struct->core.command.standby = false;

  //---------------------------
}

}
