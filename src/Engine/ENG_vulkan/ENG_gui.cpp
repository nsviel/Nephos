#include "ENG_gui.h"

#include <Engine.h>
#include <VK_drawing/VK_renderpass.h>
#include <VK_pipeline/VK_subpass.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_main/VK_engine.h>
#include <VK_struct/Struct_vulkan.h>
#include <VK_drawing/VK_viewport.h>
#include <VK_command/VK_command.h>
#include <ENG_shader/Shader.h>
#include <ENG_shader/Canvas/CAN_shader.h>


//Constructor / Destructor
ENG_gui::ENG_gui(Engine* engine){
  //---------------------------

  this->shaderManager = engine->get_shaderManager();
  this->vk_engine = engine->get_vk_engine();
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_command = new VK_command(vk_engine);
  this->vk_viewport = new VK_viewport(vk_engine);
  this->vk_pipeline = new VK_pipeline(vk_engine);
  this->vk_subpass = new VK_subpass(vk_engine);
  this->vk_renderpass = new VK_renderpass(vk_engine);

  //---------------------------
}
ENG_gui::~ENG_gui(){}

//Init function
Struct_renderpass* ENG_gui::init_renderpass(){
  //---------------------------

  //Renderpass
  Struct_renderpass* renderpass = new Struct_renderpass();
  renderpass->name = "ui";
  renderpass->subpass = "presentation";
  renderpass->draw_task = [this](Struct_renderpass* renderpass){ENG_gui::draw_gui(renderpass);};

  //Pipeline
  this->create_pipeline_canvas(renderpass);

  //---------------------------
  return renderpass;
}
void ENG_gui::create_pipeline_canvas(Struct_renderpass* renderpass){
  CAN_shader* can_shader = shaderManager->get_can_shader();
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
void ENG_gui::draw_gui(Struct_renderpass* renderpass){
  //---------------------------

  Struct_frame* frame_current = struct_vulkan->swapchain.get_frame_current();
  vk_command->start_render_pass(renderpass, frame_current, false);
  ImDrawData* draw_data = ImGui::GetDrawData();
  ImGui_ImplVulkan_RenderDrawData(draw_data, renderpass->command_buffer);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
}
