#include "Node.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk{

//Constructor / Destructor
Node::Node(utl::Node* node_utility){
  //---------------------------

  this->vk_struct = new vk::structure::Vulkan(node_utility);

  vk_struct->param.headless = false;
  if(vk_struct->param.headless) this->vk_engine = new vk::main::Headless(vk_struct);
  else this->vk_engine = new vk::main::Graphical(vk_struct);
  
  this->vk_imgui = new vk::gui::Imgui(vk_struct);
  this->vk_interface = new vk::main::Interface(vk_struct);
  this->vk_texture = new vk::image::Texture(vk_struct);
  this->vk_synchro = new vk::synchro::Synchro(vk_struct);
  this->vk_screenshot = new vk::image::Screenshot(vk_struct);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  vk_engine->init();
  vk_interface->fill_info();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  vk_engine->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  vk_synchro->wait_idle();
  vk_engine->clean();
  vk_synchro->end_idle();

  //---------------------------
}

}
