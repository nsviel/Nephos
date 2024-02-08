#include "Manager.h"

#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>


namespace vk::renderpass{

//Constructor / Destructor
Manager::Manager(vk::render::Node* node_render){
  //---------------------------

  this->rp_scene = new vk::renderpass::Scene(node_render);
  this->rp_edl = new vk::renderpass::EDL(node_render);
  this->rp_gui = new vk::renderpass::GUI(node_render);

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::init(){
  //---------------------------

  rp_scene->init_renderpass();
  rp_edl->init_renderpass();
  rp_gui->init_renderpass();

  //---------------------------
}

}
