#include "ENG_renderpass.h"

#include <Engine/Engine.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Engine/Render/Namespace.h>


namespace eng::renderpass{

//Constructor / Destructor
ENG_renderpass::ENG_renderpass(Engine* engine){
  //---------------------------

  this->rp_scene = new eng::renderpass::Scene(engine);
  this->rp_glyph = new eng::renderpass::Glyph(engine);
  this->rp_edl = new eng::renderpass::EDL(engine);
  this->rp_gui = new eng::renderpass::GUI(engine);

  //---------------------------
}
ENG_renderpass::~ENG_renderpass(){}

//Main function
void ENG_renderpass::init(){
  //---------------------------

  rp_scene->init_renderpass();
  rp_edl->init_renderpass();
  //rp_glyph->init_renderpass();
  rp_gui->init_renderpass();

  //---------------------------
}

}
