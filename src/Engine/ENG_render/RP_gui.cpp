#include "RP_gui.h"

#include <Engine.h>
#include <ENG_shader/ENG_shader.h>
#include <ENG_shader/Canvas/CAN_shader.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_main/VK_engine.h>


//Constructor / Destructor
RP_gui::RP_gui(Engine* engine){
  //---------------------------

  VK_engine* vk_engine = engine->get_vk_engine();

  this->eng_shader = engine->get_eng_shader();
  this->vk_pipeline = new VK_pipeline(vk_engine);

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
  CAN_shader* can_shader = eng_shader->get_can_shader();
  //---------------------------

  Struct_subpass* subpass = new Struct_subpass();
  subpass->target = "presentation";
  subpass->draw_task = [this](Struct_subpass* subpass){RP_gui::draw_gui(subpass);};

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->definition.name = "triangle";
  pipeline->definition.purpose = "presentation";
  pipeline->definition.topology = "triangle";
  pipeline->definition.shader = can_shader->get_shader_info("Canvas");
  subpass->vec_pipeline.push_back(pipeline);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}

//Draw function
void RP_gui::draw_gui(Struct_subpass* subpass){
  //---------------------------

  ImDrawData* draw_data = ImGui::GetDrawData();
  ImGui_ImplVulkan_RenderDrawData(draw_data, subpass->command_buffer);

  //---------------------------
}
