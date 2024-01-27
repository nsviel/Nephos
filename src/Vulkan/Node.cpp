#include "Node.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk{

//Constructor / Destructor
Node::Node(GLFWwindow* window){
  //---------------------------

  this->struct_vulkan = new vk::structure::Vulkan(window);
  this->vk_engine = new vk::main::Engine(struct_vulkan);
  this->vk_imgui = new vk::main::Imgui(struct_vulkan);
  this->vk_info = new vk::main::VK_info(struct_vulkan);
  this->vk_texture = new vk::main::VK_texture(struct_vulkan);

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

  //struct_vulkan->window.window_dim = utl_window->compute_window_dim();

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

//Parameter function
void Node::param(utl::element::Window* utl_window, bool headless){
  //---------------------------


  //---------------------------
}

}
