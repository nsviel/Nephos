#include "Event.h"

#include <Vulkan/Namespace.h>


namespace vk::window{

//Constructor / Destructor
Event::Event(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Event::~Event(){}

//Main function
void Event::wait_event(){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  glfwWaitEvents();

  //---------------------------
}
void Event::window_close_event(){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  bool window_closing = glfwWindowShouldClose(vk_struct->window.handle);
  if(window_closing){
    vk_struct->window.running = false;
  }

  //---------------------------
}
void Event::window_poll_event(){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  glfwPollEvents();

  //---------------------------
}

}
