#include "EDL.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::render::pipeline{

//Constructor / Destructor
EDL::EDL(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_uniform = new vk::binding::Uniform(vk_struct);
  this->vk_sampler = new vk::binding::Sampler(vk_struct);

  //---------------------------
}
EDL::~EDL(){}

//Main function
void EDL::add_pipeline(vk::structure::Subpass& subpass){
  //---------------------------

  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  this->set_pipeline(*pipeline);
  this->set_shader(*pipeline);
  this->set_binding(*pipeline);

  //---------------------------
  subpass.vec_pipeline.push_back(pipeline);
}

//Subfunction
void EDL::set_pipeline(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.info.name = "triangle_EDL";
  pipeline.info.topology = utl::topology::TRIANGLE;
  pipeline.info.vec_attribut.push_back(vk::pipeline::XYZ);
  pipeline.info.vec_attribut.push_back(vk::pipeline::UV);

  //---------------------------
}
void EDL::set_shader(vk::structure::Pipeline& pipeline){
  //---------------------------

  utl::shader::Info* shader_info = new utl::shader::Info();
  shader_info->name = "EDL";
  shader_info->path_glsl_vs = "../media/shader/EDL/glsl/shader_edl_vs.vert";
  shader_info->path_glsl_fs = "../media/shader/EDL/glsl/shader_edl_fs.frag";
  shader_info->path_spir_vs = "../media/shader/EDL/spir/shader_edl_vs.spv";
  shader_info->path_spir_fs = "../media/shader/EDL/spir/shader_edl_fs.spv";
  shader_info->with_recompilation = false;
  shader_info->with_depth_test = true;

  //---------------------------
  pipeline.info.shader = shader_info;
}
void EDL::set_binding(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk::binding::structure::Required sampler_color = vk_sampler->sampler_color();
  vk::binding::structure::Required sampler_depth = vk_sampler->sampler_depth();
  vk::binding::structure::Required uniform_edl = vk_uniform->uniform_edl();

  pipeline.binding.vec_required_binding.push_back(sampler_color);
  pipeline.binding.vec_required_binding.push_back(sampler_depth);
  pipeline.binding.vec_required_binding.push_back(uniform_edl);

  //---------------------------
}

}