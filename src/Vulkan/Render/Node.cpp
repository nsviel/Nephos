#include "Node.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::render{

//Constructor / Destructor
Node::Node(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_drawer = new vk::draw::Graphical(vk_struct);
  this->vk_profiler = new vk::main::Profiler(vk_struct);
  this->rp_scene = new vk::render::geometry::Renderpass(vk_struct);
  this->rp_edl = new vk::render::edl::Renderpass(vk_struct);
  this->rp_gui = new vk::render::onscreen::Renderpass(vk_struct);

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
void Node::loop(){
  //---------------------------

  vk_profiler->clear();
  vk_drawer->draw_frame();

  //---------------------------
}

}
