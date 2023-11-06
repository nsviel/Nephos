#include "RP_gui.h"

#include <Engine.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_main/VK_engine.h>
#include <VK_struct/Struct_vulkan.h>
#include <VK_drawing/VK_viewport.h>
#include <VK_command/VK_command.h>
#include <ENG_shader/ENG_shader.h>
#include <ENG_shader/Canvas/CAN_shader.h>


//Constructor / Destructor
RP_gui::RP_gui(Engine* engine){
  //---------------------------

  this->eng_shader = engine->get_eng_shader();
  this->vk_engine = engine->get_vk_engine();
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_command = new VK_command(vk_engine);
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
  renderpass->subpass_trg = "presentation";
  renderpass->draw_task = [this](Struct_renderpass* renderpass){RP_gui::draw_gui(renderpass);};

  //Pipeline
  this->create_pipeline_canvas(renderpass);

  //---------------------------
  return renderpass;
}
void RP_gui::create_pipeline_canvas(Struct_renderpass* renderpass){
  CAN_shader* can_shader = eng_shader->get_can_shader();
  //---------------------------

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->definition.name = "triangle";
  pipeline->definition.purpose = "ui";
  pipeline->definition.topology = "triangle";
  pipeline->definition.shader = can_shader->get_shader_info("Canvas");
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}

//Draw function
void RP_gui::draw_gui(Struct_renderpass* renderpass){
  //---------------------------

  Struct_framebuffer* frame_current = struct_vulkan->swapchain.get_frame_presentation();
  vk_command->start_render_pass(renderpass, frame_current, false);
  ImDrawData* draw_data = ImGui::GetDrawData();
  ImGui_ImplVulkan_RenderDrawData(draw_data, renderpass->command_buffer);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
}
