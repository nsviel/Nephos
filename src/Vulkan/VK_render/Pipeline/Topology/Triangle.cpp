#include "Triangle.h"

#include <Vulkan/Namespace.h>


namespace vk::render::pipeline{

//Constructor / Destructor
Triangle::Triangle(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::binding::Uniform(vk_struct);

  //---------------------------
}
Triangle::~Triangle(){}

//Main function
void Triangle::add_pipeline(vk::structure::Subpass& subpass){
  //---------------------------

  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  this->set_pipeline(*pipeline);
  this->set_shader(*pipeline);
  this->set_binding(*pipeline);

  //---------------------------
  subpass.map_pipeline["triangle"] = pipeline;
}

//Subfunction
void Triangle::set_pipeline(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.info.topology = utl::topology::TRIANGLE;
  pipeline.info.vec_attribut.push_back(vk::pipeline::XYZ);
  pipeline.info.vec_attribut.push_back(vk::pipeline::RGBA);

  //---------------------------
}
void Triangle::set_shader(vk::structure::Pipeline& pipeline){
  //---------------------------

  utl::shader::Info* shader_info = new utl::shader::Info();
  shader_info->name = "Triangle";
  shader_info->path_glsl_vs = "../media/shader/Scene/glsl/line_vs.vert";
  shader_info->path_glsl_fs = "../media/shader/Scene/glsl/line_fs.frag";
  shader_info->path_spir_vs = "../media/shader/Topology/spir/line_vs.spv";
  shader_info->path_spir_fs = "../media/shader/Topology/spir/line_fs.spv";
  shader_info->with_recompilation = false;
  shader_info->with_depth_test = true;

  //---------------------------
  pipeline.info.shader = shader_info;
}
void Triangle::set_binding(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk::binding::structure::Required descriptor;
  descriptor = vk_uniform->uniform_mvp();
  pipeline.binding.vec_required_binding.push_back(descriptor);

  //---------------------------
}

}
