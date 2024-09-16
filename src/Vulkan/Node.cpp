#include "Node.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk{

//Constructor / Destructor
Node::Node(bool* running){
  //---------------------------

  this->vk_struct = new vk::Structure(running);
  this->vk_core = new vk::core::Node(vk_struct);
  this->vk_render = new vk::render::Render(vk_struct);
  this->vk_imgui = new vk::gui::Imgui(vk_struct);
  this->vk_texture = new vk::image::Texture(vk_struct);
  this->vk_synchro = new vk::synchro::Synchro(vk_struct);
  this->vk_screenshot = new vk::image::Screenshot(vk_struct);
  this->vk_data = new vk::data::Data(vk_struct);
  this->vk_window = new vk::window::GLFW(vk_struct);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  vk_window->init();
  vk_render->init();
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

  vk_synchro->wait_idle_and_pause();
  vk_core->clean();
  vk_window->clean();

  //---------------------------
}

}
