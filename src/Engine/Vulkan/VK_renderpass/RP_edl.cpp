#include "RP_edl.h"

#include <Engine.h>
#include <Shader/Shader.h>
#include <Shader/EDL/EDL_shader.h>
#include <Shader/EDL/EDL_param.h>
#include <Vulkan/VK_renderpass/VK_renderpass.h>
#include <Vulkan/VK_pipeline/VK_subpass.h>
#include <Vulkan/VK_pipeline/VK_pipeline.h>
#include <Vulkan/VK_engine.h>
#include <Vulkan/VK_struct.h>
#include <Vulkan/VK_camera/VK_viewport.h>



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

  //Pipeline creation
  Struct_pipeline* pipeline_edl = create_pipeline_edl(renderpass);

  //Renderpass
  renderpass->name = "edl";
  vk_subpass->create_subpass_shader(renderpass);
  renderpass->vec_pipeline.push_back(pipeline_edl);

  //---------------------------
  vk_renderpass->create_renderpass(renderpass);
}

//Pipeline
Struct_pipeline* RP_edl::create_pipeline_edl(Struct_renderpass* renderpass){
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

  //---------------------------
  return pipeline;
}
void RP_edl::recreate_pipeline_edl(){
  //---------------------------

  Struct_pipeline* pipeline_new = create_pipeline_edl(&vk_struct->renderpass_edl);
  vk_pipeline->create_pipeline(&vk_struct->renderpass_edl, pipeline_new);

  vkDeviceWaitIdle(vk_struct->device.device);

  Struct_pipeline* pipeline_old = vk_pipeline->get_pipeline_byName(&vk_struct->renderpass_edl, "triangle_EDL");
  vk_pipeline->clean_pipeline(pipeline_old);

  vk_struct->renderpass_edl.vec_pipeline.clear();
  vk_struct->renderpass_edl.vec_pipeline.push_back(pipeline_new);

  //---------------------------
}
