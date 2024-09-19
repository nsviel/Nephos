#include "Point.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::pipeline::dyn{

//Constructor / Destructor
Point::Point(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_sampler = new vk::descriptor::Sampler(vk_struct);

  //---------------------------
}
Point::~Point(){}

//Main function
void Point::add_pipeline(vk::structure::Subpass& subpass){
  std::shared_ptr<vk::structure::Pipeline> pipeline = std::make_shared<vk::structure::Pipeline>();
  pipeline->subpass_ID = subpass.index;
  //---------------------------

  this->set_pipeline(*pipeline);
  this->set_shader(*pipeline);
  this->set_binding(*pipeline);

  //---------------------------
  subpass.map_pipeline["dynamic_point"] = pipeline;
}

//Subfunction
void Point::set_pipeline(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.info.topology = utl::topology::POINT;
  pipeline.info.vec_attribut.push_back(vk::attribut::UV);

  //---------------------------
}
void Point::set_shader(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk::shader::structure::Info shader_info;
  shader_info.name = "dynamic_point";
  shader_info.path_glsl.vs = "../media/shader/Dynamic/glsl/point_vs.vert";
  shader_info.path_glsl.fs = "../media/shader/Dynamic/glsl/point_fs.frag";
  shader_info.path_spir.vs = "../media/shader/Dynamic/spir/point_vs.spv";
  shader_info.path_spir.fs = "../media/shader/Dynamic/spir/point_fs.spv";
  shader_info.with_recompilation = true;
  shader_info.with_depth_test = true;

  //---------------------------
  pipeline.shader.info = shader_info;
}
void Point::set_binding(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.descriptor.layout.vec_descriptor.push_back(vk::pipeline::dyn::sampler_color());
  pipeline.descriptor.layout.vec_descriptor.push_back(vk::pipeline::dyn::sampler_depth());
  pipeline.descriptor.layout.vec_descriptor.push_back(vk::pipeline::dyn::uniform_mvp());
  pipeline.descriptor.layout.vec_descriptor.push_back(vk::pipeline::dyn::uniform_point_size());
  pipeline.descriptor.layout.vec_descriptor.push_back(vk::pipeline::dyn::uniform_dynamic());

  //---------------------------
}

}
