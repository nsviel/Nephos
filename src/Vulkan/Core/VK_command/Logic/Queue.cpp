#include "Queue.h"

#include <Vulkan/Namespace.h>


namespace vk::command{

//Constructor / Destructor
Queue::Queue(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Queue::~Queue(){}

//Main function
void Queue::init(){
  //---------------------------

  vk_struct->core.command.transfer = new vk::queue::transfer::Command(vk_struct);
  vk_struct->core.command.graphics = new vk::queue::graphics::Command(vk_struct);
  vk_struct->core.command.presentation = new vk::queue::presentation::Command(vk_struct);

  //---------------------------
}
void Queue::clean(){
  //---------------------------

  vk_struct->core.command.transfer->stop_thread();
  vk_struct->core.command.graphics->stop_thread();

  //---------------------------
}

}
