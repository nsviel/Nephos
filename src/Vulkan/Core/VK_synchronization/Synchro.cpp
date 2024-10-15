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

  vk_struct->core.command.graphics->set_pause(true);
  vk_struct->core.command.transfer->set_pause(true);

  //---------------------------
}
void Synchro::end_idle(){
  //---------------------------

  vk_struct->core.command.transfer->set_pause(false);
  vk_struct->core.command.graphics->set_pause(false);

  //---------------------------
}

}
