#include "Topology.h"

#include <Vulkan/Namespace.h>


namespace vk::render::pipeline{

//Constructor / Destructor
Topology::Topology(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::binding::Uniform(vk_struct);

  //---------------------------
}
Topology::~Topology(){}

//Main function
void Topology::add_pipeline_line(vk::structure::Subpass& subpass){
  //---------------------------

  //Add shader info - Line
  utl::shader::Info* shader_info = new utl::shader::Info();
  shader_info->name = "Line";
  shader_info->path_glsl_vs = "../media/shader/Scene/glsl/shader_line_vs.vert";
  shader_info->path_glsl_fs = "../media/shader/Scene/glsl/shader_line_fs.frag";
  shader_info->path_spir_vs = "../media/shader/Scene/spir/shader_line_vs.spv";
  shader_info->path_spir_fs = "../media/shader/Scene/spir/shader_line_fs.spv";
  shader_info->with_recompilation = false;
  shader_info->with_depth_test = true;

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
  subpass.vec_pipeline.push_back(pipeline);
}
void Topology::add_pipeline_point(vk::structure::Subpass& subpass){
  //---------------------------

  //Add shader info - Point
  utl::shader::Info* shader_info = new utl::shader::Info();
  shader_info->name = "Point";
  shader_info->path_glsl_vs = "../media/shader/Scene/glsl/shader_point_vs.vert";
  shader_info->path_glsl_fs = "../media/shader/Scene/glsl/shader_point_fs.frag";
  shader_info->path_spir_vs = "../media/shader/Scene/spir/shader_point_vs.spv";
  shader_info->path_spir_fs = "../media/shader/Scene/spir/shader_point_fs.spv";
  shader_info->with_recompilation = false;
  shader_info->with_depth_test = true;

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
  subpass.vec_pipeline.push_back(pipeline);
}
void Topology::add_pipeline_triangle(vk::structure::Subpass& subpass){
  //---------------------------

  //Add shader info - Triangle
  utl::shader::Info* shader_info = new utl::shader::Info();
  shader_info->name = "Triangle";
  shader_info->path_glsl_vs = "../media/shader/Scene/glsl/shader_line_vs.vert";
  shader_info->path_glsl_fs = "../media/shader/Scene/glsl/shader_line_fs.frag";
  shader_info->path_spir_vs = "../media/shader/Scene/spir/shader_line_vs.spv";
  shader_info->path_spir_fs = "../media/shader/Scene/spir/shader_line_fs.spv";
  shader_info->with_recompilation = false;
  shader_info->with_depth_test = true;

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
  subpass.vec_pipeline.push_back(pipeline);
}

}
