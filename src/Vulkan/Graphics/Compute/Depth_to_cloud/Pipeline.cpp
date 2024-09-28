#include "Pipeline.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::geometry::pipeline::dynamic{

//Constructor / Destructor
Pipeline::Pipeline(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_pipeline = new vk::render::Pipeline(vk_struct);

  //---------------------------
}
Pipeline::~Pipeline(){}

//Main function
void Pipeline::add_pipeline(vk::structure::Subpass& subpass){
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
void Pipeline::set_pipeline(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk::pipeline::structure::Info pipeline_info{};
  pipeline_info.name = "depth_to_cloud";
  pipeline_info.topology = utl::topology::DYNAMIC_POINT;
  pipeline_info.vec_attribut.push_back(vk::attribut::XYZ);
  pipeline_info.vec_attribut.push_back(vk::attribut::RGBA);
  pipeline_info.vec_attribut.push_back(vk::attribut::UV);

  //---------------------------
  pipeline.info = pipeline_info;
}
void Pipeline::set_shader(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk::shader::structure::Info shader_info{};
  shader_info.name = "dynamic_point";
  shader_info.path_glsl.comp = "../shader/Dynamic/glsl/depth_to_cloud.comp";
  shader_info.path_spir.comp = "../shader/Dynamic/spir/depth_to_cloud.comp.spv";
  shader_info.with_recompilation = true;

  //---------------------------
  pipeline.shader.info = shader_info;
}
void Pipeline::set_binding(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.descriptor.layout.vec_descriptor.push_back(vk::geometry::sampler_color());
  pipeline.descriptor.layout.vec_descriptor.push_back(vk::geometry::sampler_depth());

  //---------------------------
}

}
