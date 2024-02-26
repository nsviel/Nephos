#include "Node.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk{

//Constructor / Destructor
Node::Node(utl::Node* node_utility){
  //---------------------------

  this->struct_vulkan = new vk::structure::Vulkan(node_utility);
  this->vk_graphical = new vk::main::Graphical(struct_vulkan);
  this->vk_imgui = new vk::main::Imgui(struct_vulkan);
  this->vk_info = new vk::main::Info(struct_vulkan);
  this->vk_texture = new vk::main::Texture(struct_vulkan);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  vk_graphical->init();
  vk_info->fill_info();

  //Save thread information
  prf::vulkan::Thread thread_prf;
  thread_prf.ID = std::this_thread::get_id();
  thread_prf.name = "Main";
  vector<prf::vulkan::Thread>& vec_thread = struct_vulkan->tasker_vulkan->get_vec_thread();
  vec_thread.push_back(thread_prf);

  //---------------------------
}
void Node::loop(){
  //---------------------------

  vk_graphical->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  vk_graphical->clean();

  //---------------------------
}
void Node::wait(){
  //---------------------------

  vk_graphical->device_wait_idle();

  //---------------------------
}

}
