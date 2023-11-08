#include "RP_gui.h"

#include <Engine.h>
#include <ENG_shader/ENG_shader.h>
#include <ENG_shader/Canvas/CAN_shader.h>
#include <VK_main/VK_imgui.h>
#include <VK_main/VK_engine.h>


//Constructor / Destructor
RP_gui::RP_gui(Engine* engine){
  //---------------------------

  this->vk_engine = engine->get_vk_engine();
  this->eng_shader = engine->get_eng_shader();

  //---------------------------
}
RP_gui::~RP_gui(){}

//Init function
Struct_renderpass* RP_gui::init_renderpass(){
  //---------------------------

  //Renderpass
  Struct_renderpass* renderpass = new Struct_renderpass();
  renderpass->name = "gui";

  //Pipeline
  this->create_subpass(renderpass);

  //---------------------------
  return renderpass;
}
void RP_gui::create_subpass(Struct_renderpass* renderpass){
  VK_imgui* vk_imgui = vk_engine->get_vk_imgui();
  CAN_shader* can_shader = eng_shader->get_can_shader();
  //---------------------------

  Struct_subpass* subpass = new Struct_subpass();
  subpass->target = "presentation";
  subpass->draw_task = [vk_imgui](Struct_subpass* subpass){vk_imgui->draw(subpass);};

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->definition.name = "triangle";
  pipeline->definition.purpose = "presentation";
  pipeline->definition.topology = "triangle";
  pipeline->definition.shader = can_shader->get_shader_info("Canvas");
  subpass->vec_pipeline.push_back(pipeline);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}
