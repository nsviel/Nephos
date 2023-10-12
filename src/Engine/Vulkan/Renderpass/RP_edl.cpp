#include "RP_edl.h"

#include <Engine.h>
#include <Shader/EDL/EDL_param.h>
#include <Vulkan/Renderpass/VK_renderpass.h>
#include <Vulkan/Pipeline/VK_subpass.h>
#include <Vulkan/Pipeline/VK_pipeline.h>
#include <Vulkan/VK_engine.h>
#include <Vulkan/VK_struct.h>
#include <Vulkan/Camera/VK_viewport.h>
#include <Shader/Shader.h>
#include <Shader/EDL/EDL_shader.h>


//Constructor / Destructor
RP_edl::RP_edl(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_struct = vk_engine->get_vk_struct();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_viewport = vk_engine->get_vk_viewport();
  this->vk_subpass = new VK_subpass(vk_engine);

  //---------------------------
}
RP_edl::~RP_edl(){
  //---------------------------

  delete vk_subpass;

  //---------------------------
}

//Main function
void RP_edl::init_renderpass(Struct_renderpass* renderpass){
  VK_renderpass* vk_renderpass = vk_engine->get_vk_renderpass();
  //---------------------------

  //Renderpass
  renderpass->name = "edl";
  vk_subpass->create_subpass_shader(renderpass);
  this->create_pipeline_edl(renderpass);

  //---------------------------
  vk_renderpass->create_renderpass(renderpass);
}

//Pipeline
void RP_edl::create_pipeline_edl(Struct_renderpass* renderpass){
  //---------------------------

  Engine* engine = vk_engine->get_engine();
  Shader* shaderManager = engine->get_shaderManager();
  EDL_shader* edl_shader = shaderManager->get_edl_shader();

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "triangle_EDL";
  pipeline->topology = "triangle";
  pipeline->purpose = "graphics";
  pipeline->shader_info = edl_shader->get_shader_info("EDL");
  pipeline->info.vec_data_name.push_back("location");
  pipeline->info.vec_data_name.push_back("tex_coord");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_color", 0, 1, TYPE_SAMPLER, STAGE_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_depth", 0, 4, TYPE_SAMPLER, STAGE_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("EDL_param", sizeof(EDL_param), 5, TYPE_UNIFORM, STAGE_FS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}
