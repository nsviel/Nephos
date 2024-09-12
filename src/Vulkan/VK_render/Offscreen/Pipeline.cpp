#include "Pipeline.h"

#include <Vulkan/Namespace.h>


namespace vk::render::offscreen{

//Constructor / Destructor
Pipeline::Pipeline(vk::Structure* vk_struct, vk::render::offscreen::Shader* vk_shader){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_shader = vk_shader;
  this->vk_uniform = new vk::binding::Uniform(vk_struct);
  this->vk_drawer = new vk::render::offscreen::Drawer(vk_struct);

  //---------------------------
}
Pipeline::~Pipeline(){}

//Main function
void Pipeline::create_pipeline_line(vk::structure::Subpass* subpass){
  //---------------------------

  //Shader
  utl::shader::Info* shader_info = vk_shader->get_shader_info("Line");

  //Pipeline
  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  pipeline->info.name = "line";
  pipeline->info.topology = utl::topology::LINE;
  pipeline->info.shader = shader_info;
  pipeline->info.vec_attribut.push_back(vk::pipeline::XYZ);
  pipeline->info.vec_attribut.push_back(vk::pipeline::RGBA);

  //Descriptor
  vk::binding::structure::Required descriptor;
  descriptor = vk_uniform->uniform_mvp();
  pipeline->binding.vec_required_binding.push_back(descriptor);

  //---------------------------
  subpass->vec_pipeline.push_back(pipeline);
}
void Pipeline::create_pipeline_point(vk::structure::Subpass* subpass){
  //---------------------------

  //Shader
  utl::shader::Info* shader_info = vk_shader->get_shader_info("Point");

  //Pipeline
  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  pipeline->info.name = "point";
  pipeline->info.topology = utl::topology::POINT;
  pipeline->info.shader = shader_info;
  pipeline->info.vec_attribut.push_back(vk::pipeline::XYZ);
  pipeline->info.vec_attribut.push_back(vk::pipeline::RGBA);

  //Descriptor
  vk::binding::structure::Required descriptor;
  descriptor = vk_uniform->uniform_mvp();
  pipeline->binding.vec_required_binding.push_back(descriptor);
  descriptor = vk_uniform->uniform_point_size();
  pipeline->binding.vec_required_binding.push_back(descriptor);

  //---------------------------
  subpass->vec_pipeline.push_back(pipeline);
}
void Pipeline::create_pipeline_triangle(vk::structure::Subpass* subpass){
  //---------------------------

  //Shader
  utl::shader::Info* shader_info = vk_shader->get_shader_info("Triangle");

  //Pipeline
  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  pipeline->info.name = "triangle";
  pipeline->info.topology = utl::topology::TRIANGLE;
  pipeline->info.shader = shader_info;
  pipeline->info.vec_attribut.push_back(vk::pipeline::XYZ);
  pipeline->info.vec_attribut.push_back(vk::pipeline::RGBA);

  //Descriptor
  vk::binding::structure::Required descriptor;
  descriptor = vk_uniform->uniform_mvp();
  pipeline->binding.vec_required_binding.push_back(descriptor);

  //---------------------------
  subpass->vec_pipeline.push_back(pipeline);
}

}
