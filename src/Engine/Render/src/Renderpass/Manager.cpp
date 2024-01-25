#include "Manager.h"

#include <Engine/Engine.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Engine/Render/Namespace.h>


namespace eng::renderpass{

//Constructor / Destructor
Manager::Manager(Engine* engine){
  //---------------------------

  this->rp_scene = new eng::renderpass::Scene(engine);
  this->rp_glyph = new eng::renderpass::Glyph(engine);
  this->rp_edl = new eng::renderpass::EDL(engine);
  this->rp_gui = new eng::renderpass::GUI(engine);

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::init(){
  //---------------------------

  rp_scene->init_renderpass();
  rp_edl->init_renderpass();
  //rp_glyph->init_renderpass();
  rp_gui->init_renderpass();

  //---------------------------
}

}
