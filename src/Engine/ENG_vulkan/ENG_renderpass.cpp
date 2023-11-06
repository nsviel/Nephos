#include "ENG_renderpass.h"

#include <Engine.h>
#include <VK_main/VK_engine.h>
#include <ENG_vulkan/ENG_scene.h>
#include <ENG_vulkan/ENG_edl.h>
#include <ENG_vulkan/ENG_gui.h>


//Constructor / Destructor
ENG_renderpass::ENG_renderpass(Engine* engine){
  //---------------------------

  VK_engine* vk_engine = engine->get_vk_engine();
  this->eng_scene = new ENG_scene(vk_engine);
  this->eng_edl = new ENG_edl(vk_engine);
  this->eng_gui = new ENG_gui(vk_engine);

  //---------------------------
}
ENG_renderpass::~ENG_renderpass(){}

//Main function
void ENG_renderpass::init_renderpass(){
  //---------------------------

  eng_scene->init_renderpass();
  eng_edl->init_renderpass();
  eng_gui->init_renderpass();

  //---------------------------
}
