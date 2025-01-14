#include "Pipeline.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::gfx::edl{

//Constructor / Destructor
Pipeline::Pipeline(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_sampler = new vk::descriptor::Sampler(vk_struct);
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
  subpass.map_pipeline["edl"] = pipeline;
}

//Subfunction
void Pipeline::set_pipeline(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.info.name = "edl";
  pipeline.info.topology = utl::topology::TRIANGLE;
  pipeline.info.vec_attribut.push_back(vk::attribut::XYZ);
  pipeline.info.vec_attribut.push_back(vk::attribut::UV);

  //---------------------------
}
void Pipeline::set_shader(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk::shader::structure::Info shader_info;
  shader_info.name = "EDL";
  shader_info.path_glsl.vs = "../shader/EDL/glsl/edl_vs.vert";
  shader_info.path_glsl.fs = "../shader/EDL/glsl/edl_fs.frag";
  shader_info.path_spir.vs = "../shader/EDL/spir/edl_vs.spv";
  shader_info.path_spir.fs = "../shader/EDL/spir/edl_fs.spv";
  shader_info.with_recompilation = true;
  shader_info.with_depth_test = true;

  //---------------------------
  pipeline.shader.info = shader_info;
}
void Pipeline::set_binding(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.descriptor.layout.vec_descriptor.push_back(vk::gfx::edl::sampler_color());
  pipeline.descriptor.layout.vec_descriptor.push_back(vk::gfx::edl::sampler_depth());
  pipeline.descriptor.layout.vec_descriptor.push_back(vk::gfx::edl::uniform_edl());

  //---------------------------
}

}
