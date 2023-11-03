//Pyramidal Surface Representation
#include "RP_psr.h"

#include <VK_renderpass/VK_renderpass.h>
#include <VK_pipeline/VK_subpass.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_engine.h>
#include <VK_struct.h>
#include <VK_camera/VK_viewport.h>
#include <ENG_shader/PSR/PSR_param.h>


//Constructor / Destructor
RP_psr::RP_psr(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_struct = vk_engine->get_vk_struct();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_viewport = vk_engine->get_vk_viewport();
  this->vk_subpass = new VK_subpass(vk_engine);

  //---------------------------
}
RP_psr::~RP_psr(){
  //---------------------------

  delete vk_subpass;

  //---------------------------
}

//Main function
void RP_psr::init_renderpass(Struct_renderpass* renderpass){
  VK_renderpass* vk_renderpass = vk_engine->get_vk_renderpass();
  //---------------------------

  //Renderpass
  renderpass->name = "psr";
  renderpass->color_image_usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  renderpass->color_sampler_layout = IMAGE_LAYOUT_SHADER_READONLY;
  renderpass->depth_image_usage = IMAGE_USAGE_DEPTH;
  renderpass->depth_sampler_layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

  //Subpass
  this->create_subpass_pyramid(renderpass);

  //pipeline
  this->create_pipeline_canvas(renderpass);
  //this->create_pipeline_pyramid(renderpass);

  //---------------------------
  vk_renderpass->create_renderpass(renderpass);
}

//Subpass
void RP_psr::create_subpass_pyramid(Struct_renderpass* renderpass){
  //---------------------------

  Struct_subpass* subpass = new Struct_subpass();
  subpass->attached_color.item = 0;
  subpass->attached_color.load_operation = ATTACHMENT_LOADOP_CLEAR;
  subpass->attached_color.store_operation = ATTACHMENT_STOREOP_NOTHING;
  subpass->attached_color.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->attached_color.layout_final = IMAGE_LAYOUT_SHADER_READONLY;

  subpass->attached_depth.item = 1;
  subpass->attached_depth.load_operation = ATTACHMENT_LOADOP_CLEAR;
  subpass->attached_depth.store_operation = ATTACHMENT_STOREOP_STORE;
  subpass->attached_depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->attached_depth.layout_final = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  renderpass->vec_subpass.push_back(subpass);

  //---------------------------
}

//Pipeline
void RP_psr::create_pipeline_canvas(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "triangle";
  pipeline->topology = "triangle";
  pipeline->info.vec_data_name.push_back("location");
  pipeline->info.vec_data_name.push_back("tex_coord");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_position", 0, 0, TYPE_SAMPLER, STAGE_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_color", 0, 1, TYPE_SAMPLER, STAGE_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_depth", 0, 4, TYPE_SAMPLER, STAGE_FS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}
void RP_psr::create_pipeline_pyramid(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "triangle_PSR";
  pipeline->topology = "triangle";
  pipeline->info.vec_data_name.push_back("location");
  pipeline->info.vec_data_name.push_back("tex_coord");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_position_scene", 0, 0, TYPE_SAMPLER, STAGE_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_depth_scene", 0, 1, TYPE_SAMPLER, STAGE_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("Struct_psr", sizeof(PSR_param), 2, TYPE_UNIFORM, STAGE_FS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}
