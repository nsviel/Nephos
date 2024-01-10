#include "ENG_renderpass.h"

#include <Engine/Engine.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Engine/Render/RP_scene.h>
#include <Engine/Render/RP_glyph.h>
#include <Engine/Render/RP_edl.h>
#include <Engine/Render/RP_gui.h>


//Constructor / Destructor
ENG_renderpass::ENG_renderpass(Engine* engine){
  //---------------------------

  this->rp_scene = new RP_scene(engine);
  this->rp_glyph = new RP_glyph(engine);
  this->rp_edl = new RP_edl(engine);
  this->rp_gui = new RP_gui(engine);

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
