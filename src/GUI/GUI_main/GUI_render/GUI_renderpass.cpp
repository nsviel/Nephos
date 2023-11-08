#include "GUI_renderpass.h"

#include <GUI.h>
#include <ENG_shader/ENG_shader.h>
#include <ENG_shader/Canvas/CAN_shader.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_main/VK_engine.h>


//Constructor / Destructor
GUI_renderpass::GUI_renderpass(GUI* engine){
  //---------------------------
/*
  VK_engine* vk_engine = engine->get_vk_engine();

  this->eng_shader = engine->get_eng_shader();
  this->vk_viewport = new VK_viewport(vk_engine);
  this->vk_pipeline = new VK_pipeline(vk_engine);
*/
  //---------------------------
}
GUI_renderpass::~GUI_renderpass(){}

//Init function
void GUI_renderpass::init_renderpass(){
  //---------------------------
/*
  Struct_renderpass* renderpass = new Struct_renderpass();
  renderpass->name = "gui";
  this->create_subpass(renderpass);

  vk_render->add_renderpass_description(renderpass);
*/
  //---------------------------
}
void GUI_renderpass::create_subpass(Struct_renderpass* renderpass){
/*  CAN_shader* can_shader = eng_shader->get_can_shader();
  //---------------------------

  Struct_subpass* subpass = new Struct_subpass();
  subpass->target = "presentation";
  subpass->draw_task = [this](Struct_subpass* subpass){GUI_renderpass::draw_gui(subpass);};

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->definition.name = "triangle";
  pipeline->definition.purpose = "ui";
  pipeline->definition.topology = "triangle";
  pipeline->definition.shader = can_shader->get_shader_info("Canvas");
  subpass->vec_pipeline.push_back(pipeline);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);*/
}

//Draw function
void GUI_renderpass::draw_gui(Struct_subpass* subpass){
  //---------------------------

  ImDrawData* draw_data = ImGui::GetDrawData();
  ImGui_ImplVulkan_RenderDrawData(draw_data, subpass->command_buffer);

  //---------------------------
}
