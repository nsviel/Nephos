#include "Node.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::render{

//Constructor / Destructor
Node::Node(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_drawer = new vk::draw::Graphical(vk_struct);
  this->vk_renderpass = new vk::render::Renderpass(vk_struct);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  vk_renderpass->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  vk_drawer->draw_frame();

  //---------------------------
}

}
