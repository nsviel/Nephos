#include "Triangle.h"

#include <Vulkan/Namespace.h>


namespace vk::pipeline::topology{

//Constructor / Destructor
Triangle::Triangle(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_pipeline = new vk::pipeline::Pipeline(vk_struct);

  //---------------------------
}
Triangle::~Triangle(){}

//Main function
void Triangle::add_pipeline(vk::structure::Subpass& subpass){
  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  //---------------------------

  this->set_pipeline(*pipeline);
  this->set_shader(*pipeline);
  this->set_binding(*pipeline);

  //---------------------------
  vk_pipeline->add_pipeline_topology(subpass, *pipeline);
}

//Subfunction
void Triangle::set_pipeline(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.info.name = "triangle";
  pipeline.info.topology = utl::topology::TRIANGLE;
  pipeline.info.vec_attribut.push_back(vk::attribut::XYZ);
  pipeline.info.vec_attribut.push_back(vk::attribut::RGBA);
  pipeline.info.vec_attribut.push_back(vk::attribut::UV);

  //---------------------------
}
void Triangle::set_shader(vk::structure::Pipeline& pipeline){
  //---------------------------

  utl::shader::Info shader_info;
  shader_info.name = "Triangle";
  shader_info.path_glsl_vs = "../media/shader/Topology/glsl/triangle_vs.vert";
  shader_info.path_glsl_fs = "../media/shader/Topology/glsl/triangle_fs.frag";
  shader_info.path_spir_vs = "../media/shader/Topology/spir/triangle_vs.spv";
  shader_info.path_spir_fs = "../media/shader/Topology/spir/triangle_fs.spv";
  shader_info.with_recompilation = true;
  shader_info.with_depth_test = true;

  //---------------------------
  pipeline.info.shader = shader_info;
}
void Triangle::set_binding(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.descriptor.layout.vec_descriptor.push_back(vk::pipeline::topology::uniform_mvp());

  //---------------------------
}

}
