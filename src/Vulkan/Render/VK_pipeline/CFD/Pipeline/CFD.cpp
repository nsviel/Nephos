#include "CFD.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::pipeline::cfd{

//Constructor / Destructor
CFD::CFD(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_sampler = new vk::descriptor::Sampler(vk_struct);

  //---------------------------
}
CFD::~CFD(){}

//Main function
void CFD::add_pipeline(vk::structure::Subpass& subpass){
  //---------------------------

  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  this->set_pipeline(*pipeline);
  this->set_shader(*pipeline);
  this->set_binding(*pipeline);

  //---------------------------
  subpass.map_pipeline["cfd"] = pipeline;
}

//Subfunction
void CFD::set_pipeline(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.info.topology = utl::topology::TRIANGLE;
  pipeline.info.vec_attribut.push_back(vk::attribut::XYZ);
  pipeline.info.vec_attribut.push_back(vk::attribut::UV);

  //---------------------------
}
void CFD::set_shader(vk::structure::Pipeline& pipeline){
  //---------------------------

  utl::shader::Info* shader_info = new utl::shader::Info();
  shader_info->name = "CFD";
  shader_info->path_glsl_vs = "../media/shader/CFD/glsl/cfd_vs.vert";
  shader_info->path_glsl_fs = "../media/shader/CFD/glsl/cfd_fs.frag";
  shader_info->path_spir_vs = "../media/shader/CFD/spir/cfd_vs.spv";
  shader_info->path_spir_fs = "../media/shader/CFD/spir/cfd_fs.spv";
  shader_info->with_recompilation = true;
  shader_info->with_depth_test = true;

  //---------------------------
  pipeline.info.shader = shader_info;
}
void CFD::set_binding(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.descriptor.layout.vec_descriptor.push_back(vk::pipeline::cfd::sampler_color());
  pipeline.descriptor.layout.vec_descriptor.push_back(vk::pipeline::cfd::sampler_depth());
  pipeline.descriptor.layout.vec_descriptor.push_back(vk::pipeline::cfd::uniform_cfd());

  //---------------------------
}

}
