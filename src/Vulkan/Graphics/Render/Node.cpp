#include "Node.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::gfx::render{

//Constructor / Destructor
Node::Node(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->rp_scene = new vk::geometry::Renderpass(vk_struct);
  this->rp_edl = new vk::postprocess::Renderpass(vk_struct);
  this->rp_gui = new vk::gfx::presentation::Renderpass(vk_struct);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  rp_scene->init();
  rp_edl->init();
  rp_gui->init();

  //---------------------------
}

}
