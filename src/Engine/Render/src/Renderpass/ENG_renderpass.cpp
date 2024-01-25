#include "ENG_renderpass.h"

#include <Engine/Engine.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Engine/Render/Namespace.h>


//Constructor / Destructor
ENG_renderpass::ENG_renderpass(Engine* engine){
  //---------------------------

  this->rp_scene = new eng::renderpass::RP_scene(engine);
  this->rp_glyph = new eng::renderpass::RP_glyph(engine);
  this->rp_edl = new eng::renderpass::RP_edl(engine);
  this->rp_gui = new eng::renderpass::RP_gui(engine);

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
