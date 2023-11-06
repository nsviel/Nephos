#include "ENG_renderpass.h"

#include <Engine.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_render.h>
#include <ENG_vulkan/ENG_scene.h>
#include <ENG_vulkan/ENG_edl.h>
#include <ENG_vulkan/ENG_gui.h>


//Constructor / Destructor
ENG_renderpass::ENG_renderpass(Engine* engine){
  //---------------------------

  VK_engine* vk_engine = engine->get_vk_engine();
  this->vk_render = vk_engine->get_vk_render();
  this->eng_scene = new ENG_scene(engine);
  this->eng_edl = new ENG_edl(engine);
  this->eng_gui = new ENG_gui(engine);

  //---------------------------
}
ENG_renderpass::~ENG_renderpass(){}

//Main function
void ENG_renderpass::init_renderpass(){
  //---------------------------

  Struct_renderpass* renderpass;

  renderpass = eng_scene->init_renderpass();
  vk_render->add_renderpass_description(renderpass);

  renderpass = eng_edl->init_renderpass();
  vk_render->add_renderpass_description(renderpass);

  renderpass = eng_gui->init_renderpass();
  vk_render->add_renderpass_description(renderpass);

  //---------------------------
}
