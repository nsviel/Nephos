#include "Node.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk{

//Constructor / Destructor
Node::Node(utl::Node* node_utility){
  //---------------------------

  utl::element::Window* utl_window = node_utility->get_utl_window();

  this->struct_vulkan = new vk::structure::Vulkan(utl_window->get_window());
  this->vk_engine = new vk::main::Engine(struct_vulkan);
  this->vk_imgui = new vk::main::Imgui(struct_vulkan);
  this->vk_info = new vk::main::Info(struct_vulkan);
  this->vk_texture = new vk::main::Texture(struct_vulkan);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  vk_engine->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  vk_engine->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  vk_engine->clean();

  //---------------------------
}
void Node::wait(){
  //---------------------------

  vk_engine->device_wait_idle();

  //---------------------------
}

}
