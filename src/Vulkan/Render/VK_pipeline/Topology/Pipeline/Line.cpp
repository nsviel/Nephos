#include "Line.h"

#include <Vulkan/Namespace.h>


namespace vk::pipeline::topology{

//Constructor / Destructor
Line::Line(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_pipeline = new vk::pipeline::Pipeline(vk_struct);

  //---------------------------
}
Line::~Line(){}

//Main function
void Line::add_pipeline(vk::structure::Subpass& subpass){
  std::shared_ptr<vk::structure::Pipeline> pipeline = std::make_shared<vk::structure::Pipeline>();
  //---------------------------

  this->set_pipeline(*pipeline);
  this->set_shader(*pipeline);
  this->set_binding(*pipeline);

  //---------------------------
  vk_pipeline->add_pipeline_topology(subpass, pipeline);
}

//Subfunction
void Line::set_pipeline(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.info.name = "line";
  pipeline.info.topology = utl::topology::LINE;
  pipeline.info.vec_attribut.push_back(vk::attribut::XYZ);
  pipeline.info.vec_attribut.push_back(vk::attribut::RGBA);

  //---------------------------
}
void Line::set_shader(vk::structure::Pipeline& pipeline){
  //---------------------------

  utl::shader::Info shader_info;
  shader_info.name = "Line";
  shader_info.path_glsl_vs = "../media/shader/Topology/glsl/line_vs.vert";
  shader_info.path_glsl_fs = "../media/shader/Topology/glsl/line_fs.frag";
  shader_info.path_spir_vs = "../media/shader/Topology/spir/line_vs.spv";
  shader_info.path_spir_fs = "../media/shader/Topology/spir/line_fs.spv";
  shader_info.with_recompilation = true;
  shader_info.with_depth_test = true;

  //---------------------------
  pipeline.info.shader = shader_info;
}
void Line::set_binding(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.descriptor.layout.vec_descriptor.push_back(vk::pipeline::topology::uniform_mvp());

  //---------------------------
}

}
