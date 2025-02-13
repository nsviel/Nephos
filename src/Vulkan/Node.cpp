#include "Node.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
//#include <pybind11/pybind11.h>


namespace vk{

//Constructor / Destructor
Node::Node(){
  //---------------------------

  //Core
  this->vk_struct = new vk::Structure();
  this->vk_core = new vk::core::Node(vk_struct);
  this->vk_render = new vk::gfx::render::Node(vk_struct);
  this->vk_compute = new vk::gfx::compute::Node(vk_struct);
  this->vk_window = new vk::window::Node(vk_struct);

  //Interface
  this->vk_interface_data = new vk::interface::Data(vk_struct);
  this->vk_interface_texture = new vk::interface::Texture(vk_struct);
  this->vk_interface_window = new vk::interface::Window(vk_struct);
  this->vk_interface_render = new vk::interface::Render(vk_struct);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  vk_window->init();
  vk_render->init();
  vk_compute->init();
  vk_core->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  vk_core->loop();
  vk_window->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  vk_core->clean();
  vk_window->clean();

  //---------------------------
}

}
