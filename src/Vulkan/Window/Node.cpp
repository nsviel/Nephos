#include "Node.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::window{

//Constructor / Destructor
Node::Node(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_window = new vk::window::Window(vk_struct);
  this->vk_event = new vk::window::Event(vk_struct);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  vk_window->create_window();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  vk_event->window_poll_event();
  vk_event->window_close_event();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  vk_window->destroy_window();

  //---------------------------
}

}
