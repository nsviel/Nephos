#include "Manager.h"

#include <Engine/Node.h>
#include <Engine/Render/Namespace.h>


namespace eng::renderpass{

//Constructor / Destructor
Manager::Manager(eng::render::Node* node_render){
  //---------------------------

  this->rp_scene = new eng::renderpass::Scene(node_render);
  this->rp_edl = new rnd::edl::Renderpass(node_render);
  this->rp_gui = new eng::renderpass::GUI(node_render);

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
