#include "Renderpass.h"

#include <Vulkan/Namespace.h>


namespace vk::render::gui{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_renderpass = new vk::renderpass::Renderpass(vk_struct);
  this->vk_imgui = new vk::gui::Imgui(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Main function
void Renderpass::init(){
  if(vk_struct->param.headless) return;
  //---------------------------

  vk::structure::Renderpass* renderpass = new vk::structure::Renderpass();
  this->create_renderpass(renderpass);
  this->create_subpass(renderpass);

  //---------------------------
}

//Init function
void Renderpass::create_renderpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  renderpass->name = "gui";
  vk_struct->render.vec_renderpass.push_back(renderpass);

  //---------------------------
}
void Renderpass::create_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->target = vk::renderpass::PRESENTATION;
  subpass->draw_task = [this](vk::structure::Subpass* subpass){Renderpass::draw(subpass);};

  this->create_pipeline_triangle(subpass);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}
void Renderpass::create_pipeline_triangle(vk::structure::Subpass* subpass){
  //---------------------------

  //Shader
  utl::shader::Info* shader_info = new utl::shader::Info();
  shader_info->name = "Canvas";
  shader_info->path_spir_vs = "../media/shader/Empty/spir/shader_empty_vs.spv";
  shader_info->path_spir_fs = "../media/shader/Empty/spir/shader_empty_fs.spv";
  shader_info->with_recompilation = false;
  shader_info->with_depth_test = false;

  //Pipeline
  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  pipeline->info.name = "triangle";
  pipeline->info.topology = utl::topology::TRIANGLE;
  pipeline->info.shader = shader_info;

  //---------------------------
  subpass->vec_pipeline.push_back(pipeline);
}

//Draw function
void Renderpass::draw(vk::structure::Subpass* subpass){
  //---------------------------

  vk_imgui->draw(subpass->command_buffer);

  //---------------------------
}

}
