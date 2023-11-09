#include "ENG_renderpass.h"

#include <Engine.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_render.h>
#include <ENG_render/RP_scene.h>
#include <ENG_render/RP_edl.h>
#include <ENG_render/RP_gui.h>


//Constructor / Destructor
ENG_renderpass::ENG_renderpass(Engine* engine){
  //---------------------------

  VK_engine* vk_engine = engine->get_vk_engine();
  this->vk_render = vk_engine->get_vk_render();
  this->rp_scene = new RP_scene(engine);
  this->rp_edl = new RP_edl(engine);
  this->rp_gui = new RP_gui(engine);

  //---------------------------
}
ENG_renderpass::~ENG_renderpass(){}

//Main function
void ENG_renderpass::init_renderpass(){
  //---------------------------

  //rp_scene->init_renderpass();
  //rp_edl->init_renderpass();
  rp_gui->init_renderpass();

  //---------------------------
}
