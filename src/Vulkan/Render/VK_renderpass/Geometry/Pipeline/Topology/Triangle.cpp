#include "Triangle.h"

#include <Vulkan/Namespace.h>


namespace vk::geometry::pipeline::topology{

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
  std::shared_ptr<vk::structure::Pipeline> pipeline = std::make_shared<vk::structure::Pipeline>();
  pipeline->subpass_ID = subpass.index;
  //---------------------------

  this->set_pipeline(*pipeline);
  this->set_shader(*pipeline);
  this->set_binding(*pipeline);

  //---------------------------
  vk_pipeline->add_pipeline_topology(subpass, pipeline);
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

  vk::shader::structure::Info shader_info;
  shader_info.name = "Triangle";
  shader_info.path_glsl.vs = "../shader/Topology/glsl/triangle_vs.vert";
  shader_info.path_glsl.fs = "../shader/Topology/glsl/triangle_fs.frag";
  shader_info.path_spir.vs = "../shader/Topology/spir/triangle_vs.spv";
  shader_info.path_spir.fs = "../shader/Topology/spir/triangle_fs.spv";
  shader_info.with_recompilation = true;
  shader_info.with_depth_test = true;

  //---------------------------
  pipeline.shader.info = shader_info;
}
void Triangle::set_binding(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.descriptor.layout.vec_descriptor.push_back(vk::geometry::uniform_mvp());

  //---------------------------
}

}
