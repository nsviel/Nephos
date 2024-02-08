#include "Manager.h"

#include <Vulkan/Namespace.h>


namespace vk::renderpass{

//Constructor / Destructor
Manager::Manager(vk::Node* node_vulkan){
  //---------------------------

  this->rp_scene = new vk::renderpass::Scene(node_vulkan);
  this->rp_edl = new vk::renderpass::EDL(node_vulkan);
  this->rp_gui = new vk::renderpass::GUI(node_vulkan);

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
