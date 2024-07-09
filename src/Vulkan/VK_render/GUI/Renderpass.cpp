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

//Init function
void Renderpass::init_renderpass(){
  //---------------------------

  //Renderpass
  vk::structure::Renderpass* renderpass = new vk::structure::Renderpass();
  renderpass->name = "gui";

  //Pipeline
  this->create_subpass(renderpass);

  //---------------------------
  vk_struct->render.vec_renderpass.push_back(renderpass);
}
void Renderpass::create_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->target = vk::renderpass::PRESENTATION;
  subpass->draw_task = [this](vk::structure::Subpass* subpass){Renderpass::draw(subpass);};

  this->pipeline_triangle(subpass);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}
void Renderpass::pipeline_triangle(vk::structure::Subpass* subpass){
  //---------------------------

  //Shader
  utl::shader::Info* shader_info = new utl::shader::Info();
  shader_info->title = "Canvas";
  shader_info->folder = "Canvas";
  shader_info->path_spir_vs = "../media/shader/Empty/spir/shader_empty_vs.spv";
  shader_info->path_spir_fs = "../media/shader/Empty/spir/shader_empty_fs.spv";
  shader_info->compile_shader = false;
  shader_info->with_depth_test = false;

  //Pipeline
  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  pipeline->definition.name = "triangle";
  pipeline->definition.purpose = "presentation";
  pipeline->definition.topology = "triangle";
  pipeline->definition.shader = shader_info;

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
