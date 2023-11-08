#include "RP_gui.h"

#include <Engine.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_main/VK_engine.h>
#include <VK_struct/Struct_vulkan.h>
#include <VK_drawing/VK_viewport.h>
#include <ENG_shader/ENG_shader.h>
#include <ENG_shader/Canvas/CAN_shader.h>


//Constructor / Destructor
RP_gui::RP_gui(Engine* engine){
  //---------------------------

  VK_engine* vk_engine = engine->get_vk_engine();

  this->eng_shader = engine->get_eng_shader();
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_viewport = new VK_viewport(vk_engine);
  this->vk_pipeline = new VK_pipeline(vk_engine);

  //---------------------------
}
RP_gui::~RP_gui(){}

//Init function
Struct_renderpass* RP_gui::init_renderpass(){
  //---------------------------

  //Renderpass
  Struct_renderpass* renderpass = new Struct_renderpass();
  renderpass->name = "ui";

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
  renderpass->vec_subpass.push_back(subpass);

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->definition.name = "triangle";
  pipeline->definition.purpose = "ui";
  pipeline->definition.topology = "triangle";
  pipeline->definition.shader = can_shader->get_shader_info("Canvas");
  subpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}

//Draw function
void RP_gui::draw_gui(Struct_subpass* subpass){
  //---------------------------

  Struct_frame* frame = struct_vulkan->swapchain.get_frame_presentation();

  ImDrawData* draw_data = ImGui::GetDrawData();
  ImGui_ImplVulkan_RenderDrawData(draw_data, subpass->command_buffer);

  //---------------------------
}
