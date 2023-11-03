#include "RP_scene.h"

#include <Engine.h>
#include <Vulkan/VK_renderpass/VK_renderpass.h>
#include <Vulkan/VK_pipeline/VK_subpass.h>
#include <Vulkan/VK_pipeline/VK_pipeline.h>
#include <Vulkan/VK_engine.h>
#include <Vulkan/VK_struct.h>
#include <Vulkan/VK_camera/VK_viewport.h>
#include <ENG_shader/Shader.h>
#include <ENG_shader/Scene/SCE_shader.h>


//Constructor / Destructor
RP_scene::RP_scene(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_struct = vk_engine->get_vk_struct();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_viewport = vk_engine->get_vk_viewport();
  this->vk_subpass = new VK_subpass(vk_engine);

  //---------------------------
}
RP_scene::~RP_scene(){
  //---------------------------

  delete vk_subpass;

  //---------------------------
}

//Main function
void RP_scene::init_renderpass(Struct_renderpass* renderpass){
  VK_renderpass* vk_renderpass = vk_engine->get_vk_renderpass();
  //---------------------------

  renderpass->name = "scene";
  vk_subpass->create_subpass_shader(renderpass);
  this->create_pipeline_point(renderpass);
  this->create_pipeline_line(renderpass);

  //---------------------------
  vk_renderpass->create_renderpass(renderpass);
}

//Pipeline
void RP_scene::create_pipeline_point(Struct_renderpass* renderpass){
  //---------------------------

  Engine* engine = vk_engine->get_engine();
  Shader* shaderManager = engine->get_shaderManager();
  SCE_shader* sce_shader = shaderManager->get_sce_shader();

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "point";
  pipeline->topology = "point";
  pipeline->purpose = "graphics";
  pipeline->shader_info = sce_shader->get_shader_info("Point");
  pipeline->info.vec_data_name.push_back("location");
  pipeline->info.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYPE_UNIFORM, STAGE_VS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("point_size", sizeof(int), 1, TYPE_UNIFORM, STAGE_VS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}
void RP_scene::create_pipeline_line(Struct_renderpass* renderpass){
  //---------------------------

  Engine* engine = vk_engine->get_engine();
  Shader* shaderManager = engine->get_shaderManager();
  SCE_shader* sce_shader = shaderManager->get_sce_shader();

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "line";
  pipeline->topology = "line";
  pipeline->purpose = "graphics";
  pipeline->shader_info = sce_shader->get_shader_info("Line");
  pipeline->info.vec_data_name.push_back("location");
  pipeline->info.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYPE_UNIFORM, STAGE_VS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}
