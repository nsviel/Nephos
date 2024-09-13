#include "Point.h"

#include <Vulkan/Namespace.h>


namespace vk::render::pipeline{

//Constructor / Destructor
Point::Point(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::binding::Uniform(vk_struct);

  //---------------------------
}
Point::~Point(){}

//Main function
void Point::add_pipeline(vk::structure::Subpass& subpass){
  //---------------------------

  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  this->set_pipeline(*pipeline);
  this->set_shader(*pipeline);
  this->set_binding(*pipeline);

  //---------------------------
  subpass.map_pipeline["point"] = pipeline;
}

//Subfunction
void Point::set_pipeline(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.info.topology = utl::topology::POINT;
  pipeline.info.vec_attribut.push_back(vk::pipeline::XYZ);
  pipeline.info.vec_attribut.push_back(vk::pipeline::RGBA);

  //---------------------------
}
void Point::set_shader(vk::structure::Pipeline& pipeline){
  //---------------------------

  utl::shader::Info* shader_info = new utl::shader::Info();
  shader_info->name = "Point";
  shader_info->path_glsl_vs = "../media/shader/Topology/glsl/point_vs.vert";
  shader_info->path_glsl_fs = "../media/shader/Topology/glsl/point_fs.frag";
  shader_info->path_spir_vs = "../media/shader/Topology/spir/point_vs.spv";
  shader_info->path_spir_fs = "../media/shader/Topology/spir/point_fs.spv";
  shader_info->with_recompilation = false;
  shader_info->with_depth_test = true;

  //---------------------------
  pipeline.info.shader = shader_info;
}
void Point::set_binding(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.binding.vec_required_binding.push_back(vk::binding::uniform_mvp());
  pipeline.binding.vec_required_binding.push_back(vk::binding::uniform_point_size());

  //---------------------------
}

}
