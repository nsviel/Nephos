#include "Shader.h"

#include <Vulkan/Namespace.h>


namespace vk::render::edl{

Shader::Shader(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->edl_struct = new vk::render::edl::Structure();

  //---------------------------
}
Shader::~Shader(){}

//Main function
void Shader::build_shader_info(){
  //---------------------------

  //Set parameter values
  edl_struct->activated = true;
  edl_struct->strength = 15.0;
  edl_struct->radius = 1.0;

  //Add shader info
  utl::shader::Info* shader_info = new utl::shader::Info();
  shader_info->name = "EDL";
  shader_info->path_glsl_vs = "../media/shader/EDL/glsl/shader_edl_vs.vert";
  shader_info->path_glsl_fs = "../media/shader/EDL/glsl/shader_edl_fs.frag";
  shader_info->path_spir_vs = "../media/shader/EDL/spir/shader_edl_vs.spv";
  shader_info->path_spir_fs = "../media/shader/EDL/spir/shader_edl_fs.spv";
  shader_info->with_recompilation = false;
  shader_info->with_depth_test = true;
  this->vec_shader_info.push_back(shader_info);

  //---------------------------
}
void Shader::update_shader(){
  //---------------------------

  // Depth setup
  edl_struct->z_near = 0.001;
  edl_struct->z_far = 1000;

  //Dimension
  edl_struct->tex_width = vk_struct->window.dimension.x;
  edl_struct->tex_height = vk_struct->window.dimension.y;

  //---------------------------
}

}
