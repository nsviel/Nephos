#include "ENG_gui.h"

#include <Engine.h>
#include <VK_drawing/VK_renderpass.h>
#include <VK_pipeline/VK_subpass.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_main/VK_engine.h>
#include <VK_struct/struct_vulkan.h>
#include <VK_drawing/VK_viewport.h>
#include <ENG_shader/Shader.h>
#include <ENG_shader/Canvas/CAN_shader.h>


//Constructor / Destructor
ENG_gui::ENG_gui(VK_engine* vk_engine){
  //---------------------------

  this->struct_vulkan = vk_engine->get_struct_vulkan();

  this->vk_engine = vk_engine;
  this->vk_viewport = new VK_viewport(vk_engine);
  this->vk_pipeline = new VK_pipeline(vk_engine);
  this->vk_subpass = new VK_subpass(vk_engine);

  //---------------------------
}
ENG_gui::~ENG_gui(){}

//Main function
void ENG_gui::init_renderpass(){
  VK_renderpass* vk_renderpass = vk_engine->get_vk_renderpass();
  //---------------------------

  Struct_renderpass* renderpass = new Struct_renderpass();

  renderpass->name = "ui";
  vk_subpass->create_subpass_presentation(renderpass);
  this->create_pipeline_canvas(renderpass);

  //---------------------------
  vk_renderpass->create_renderpass(renderpass);
}
void ENG_gui::create_pipeline_canvas(Struct_renderpass* renderpass){
  //---------------------------

  Engine* engine = vk_engine->get_engine();
  Shader* shaderManager = engine->get_shaderManager();
  CAN_shader* can_shader = shaderManager->get_can_shader();

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "triangle";
  pipeline->purpose = "ui";
  pipeline->topology = "triangle";
  pipeline->shader_info = can_shader->get_shader_info("Canvas");
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}
