#include "Pipeline.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::compute::dtc{

//Constructor / Destructor
Pipeline::Pipeline(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_pipeline = new vk::compute::Pipeline(vk_struct);

  //---------------------------
}
Pipeline::~Pipeline(){}

//Main function
void Pipeline::create_pipeline(){
  std::shared_ptr<vk::structure::Pipeline> pipeline = std::make_shared<vk::structure::Pipeline>();
  //---------------------------

  this->set_pipeline(*pipeline);
  this->set_shader(*pipeline);
  this->set_binding(*pipeline);

  //---------------------------
  //vk_struct->core.pipeline.map_compute[pipeline->info.name] = pipeline;
}

//Subfunction
void Pipeline::set_pipeline(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk::pipeline::structure::Info pipeline_info{};
  pipeline_info.name = "depth_to_cloud";

  //---------------------------
  pipeline.info = pipeline_info;
}
void Pipeline::set_shader(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk::shader::structure::Info shader_info{};
  shader_info.name = "depth_to_cloud";
  shader_info.path_glsl.comp = "../shader/Dynamic/glsl/depth_to_cloud.comp";
  shader_info.path_spir.comp = "../shader/Dynamic/spir/depth_to_cloud.comp.spv";
  shader_info.with_recompilation = true;

  //---------------------------
  pipeline.shader.info = shader_info;
}
void Pipeline::set_binding(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.descriptor.layout.vec_descriptor.push_back(vk::compute::dtc::sampler_depth());

  //---------------------------
}

}
