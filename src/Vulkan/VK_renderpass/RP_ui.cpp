#include "RP_ui.h"

#include <Engine.h>
#include <VK_renderpass/VK_renderpass.h>
#include <VK_pipeline/VK_subpass.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_engine.h>
#include <VK_struct.h>
#include <VK_camera/VK_viewport.h>
#include <ENG_shader/Shader.h>
#include <ENG_shader/Canvas/CAN_shader.h>


//Constructor / Destructor
RP_ui::RP_ui(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_struct = vk_engine->get_vk_struct();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_viewport = vk_engine->get_vk_viewport();
  this->vk_subpass = new VK_subpass(vk_engine);

  //---------------------------
}
RP_ui::~RP_ui(){
  //---------------------------

  delete vk_subpass;

  //---------------------------
}

//Main function
void RP_ui::init_renderpass(Struct_renderpass* renderpass){
  VK_renderpass* vk_renderpass = vk_engine->get_vk_renderpass();
  //---------------------------

  renderpass->name = "ui";
  vk_subpass->create_subpass_presentation(renderpass);
  this->create_pipeline_canvas(renderpass);

  //---------------------------
  vk_renderpass->create_renderpass(renderpass);
}

//Pipeline
void RP_ui::create_pipeline_canvas(Struct_renderpass* renderpass){
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
