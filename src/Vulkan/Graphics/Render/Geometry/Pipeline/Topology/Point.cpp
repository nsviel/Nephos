#include "Point.h"

#include <Vulkan/Namespace.h>


namespace vk::geometry::pipeline::topology{

//Constructor / Destructor
Point::Point(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_pipeline = new vk::pipeline::gfx::Pipeline(vk_struct);

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
  vk_pipeline->add_pipeline_topology(subpass, pipeline);
}

//Subfunction
void Point::set_pipeline(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk::pipeline::structure::Info pipeline_info{};
  pipeline_info.name = "point";
  pipeline_info.topology = utl::topology::POINT;
  pipeline_info.vec_attribut.push_back(vk::attribut::XYZ);
  pipeline_info.vec_attribut.push_back(vk::attribut::RGBA);
  pipeline_info.type = vk::pipeline::RENDER;

  //---------------------------
  pipeline.info = pipeline_info;
}
void Point::set_shader(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk::shader::structure::Info shader_info;
  shader_info.name = "Point";
  shader_info.path_glsl.vs = "../shader/Topology/glsl/point_vs.vert";
  shader_info.path_glsl.fs = "../shader/Topology/glsl/point_fs.frag";
  shader_info.path_spir.vs = "../shader/Topology/spir/point_vs.spv";
  shader_info.path_spir.fs = "../shader/Topology/spir/point_fs.spv";
  shader_info.with_recompilation = true;
  shader_info.with_depth_test = true;

  //---------------------------
  pipeline.shader.info = shader_info;
}
void Point::set_binding(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.descriptor.layout.vec_descriptor.push_back(vk::geometry::uniform_mvp());
  pipeline.descriptor.layout.vec_descriptor.push_back(vk::geometry::uniform_point_size());

  //---------------------------
}

}
