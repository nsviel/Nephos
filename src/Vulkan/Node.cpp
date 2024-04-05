#include "Node.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk{

//Constructor / Destructor
Node::Node(utl::Node* node_utility){
  //---------------------------

  this->vk_struct = new vk::structure::Vulkan(node_utility);
  this->vk_graphical = new vk::main::Graphical(vk_struct);
  this->vk_imgui = new vk::main::Imgui(vk_struct);
  this->vk_info = new vk::main::Info(vk_struct);
  this->vk_texture = new vk::main::Texture(vk_struct);
  this->vk_synchro = new vk::synchro::Synchro(vk_struct);
  this->vk_screenshot = new vk::image::Screenshot(vk_struct);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  vk_graphical->init();
  vk_info->fill_info();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  vk_graphical->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  vk_synchro->wait_idle();
  vk_graphical->clean();
  vk_synchro->end_idle();

  //---------------------------
}

}
