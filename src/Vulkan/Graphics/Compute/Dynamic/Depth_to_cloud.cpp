#include "Depth_to_cloud.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::geometry::pipeline::dynamic{

//Constructor / Destructor
Depth_to_cloud::Depth_to_cloud(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_pipeline = new vk::render::Pipeline(vk_struct);

  //---------------------------
}
Depth_to_cloud::~Depth_to_cloud(){}

//Main function
void Depth_to_cloud::add_pipeline(vk::structure::Subpass& subpass){
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
void Depth_to_cloud::set_pipeline(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk::pipeline::structure::Info pipeline_info{};
  pipeline_info.name = "dynamic_point";
  pipeline_info.topology = utl::topology::DYNAMIC_POINT;
  pipeline_info.vec_attribut.push_back(vk::attribut::XYZ);
  pipeline_info.vec_attribut.push_back(vk::attribut::RGBA);
  pipeline_info.vec_attribut.push_back(vk::attribut::UV);

  //---------------------------
  pipeline.info = pipeline_info;
}
void Depth_to_cloud::set_shader(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk::shader::structure::Info shader_info{};
  shader_info.name = "dynamic_point";
  shader_info.path_glsl.vs = "../shader/Dynamic/glsl/point_vs.vert";
  shader_info.path_glsl.fs = "../shader/Dynamic/glsl/point_fs.frag";
  shader_info.path_spir.vs = "../shader/Dynamic/spir/point_vs.spv";
  shader_info.path_spir.fs = "../shader/Dynamic/spir/point_fs.spv";
  shader_info.with_recompilation = true;
  shader_info.with_depth_test = true;

  //---------------------------
  pipeline.shader.info = shader_info;
}
void Depth_to_cloud::set_binding(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.descriptor.layout.vec_descriptor.push_back(vk::geometry::uniform_mvp());
  pipeline.descriptor.layout.vec_descriptor.push_back(vk::geometry::uniform_point_size());
  pipeline.descriptor.layout.vec_descriptor.push_back(vk::geometry::uniform_dynamic());
  pipeline.descriptor.layout.vec_descriptor.push_back(vk::geometry::sampler_color());
  pipeline.descriptor.layout.vec_descriptor.push_back(vk::geometry::sampler_depth());

  //---------------------------
}

}
