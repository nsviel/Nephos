#include "Node.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::window{

//Constructor / Destructor
Node::Node(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_window = new vk::window::GLFW(vk_struct);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  vk_window->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  vk_window->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  vk_window->clean();

  //---------------------------
}

}
