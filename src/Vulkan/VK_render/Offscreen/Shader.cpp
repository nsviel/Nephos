#include "Shader.h"

#include <Vulkan/Namespace.h>


namespace vk::render::offscreen{

Shader::Shader(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Shader::~Shader(){}

//Main function
void Shader::build_shader_info(){
  //---------------------------

  this->init_shader_line();
  this->init_shader_point();
  this->init_shader_triangle();

  //---------------------------
}

//Subfunction
void Shader::init_shader_line(){
  //---------------------------

  //Add shader info - Line
  utl::shader::Info* shader_info = new utl::shader::Info();
  shader_info->name = "Line";
  shader_info->path_glsl_vs = "../media/shader/Scene/glsl/shader_line_vs.vert";
  shader_info->path_glsl_fs = "../media/shader/Scene/glsl/shader_line_fs.frag";
  shader_info->path_spir_vs = "../media/shader/Scene/spir/shader_line_vs.spv";
  shader_info->path_spir_fs = "../media/shader/Scene/spir/shader_line_fs.spv";
  shader_info->with_recompilation = false;
  shader_info->with_depth_test = true;
  this->vec_shader_info.push_back(shader_info);

  //---------------------------
}
void Shader::init_shader_point(){
  //---------------------------

  //Add shader info - Point
  utl::shader::Info* shader_info = new utl::shader::Info();
  shader_info->name = "Point";
  shader_info->path_glsl_vs = "../media/shader/Scene/glsl/shader_point_vs.vert";
  shader_info->path_glsl_fs = "../media/shader/Scene/glsl/shader_point_fs.frag";
  shader_info->path_spir_vs = "../media/shader/Scene/spir/shader_point_vs.spv";
  shader_info->path_spir_fs = "../media/shader/Scene/spir/shader_point_fs.spv";
  shader_info->with_recompilation = false;
  shader_info->with_depth_test = true;
  this->vec_shader_info.push_back(shader_info);

  //---------------------------
}
void Shader::init_shader_triangle(){
  //---------------------------

  //Add shader info - Triangle
  utl::shader::Info* shader_info = new utl::shader::Info();
  shader_info->name = "Triangle";
  shader_info->path_glsl_vs = "../media/shader/Scene/glsl/shader_line_vs.vert";
  shader_info->path_glsl_fs = "../media/shader/Scene/glsl/shader_line_fs.frag";
  shader_info->path_spir_vs = "../media/shader/Scene/spir/shader_line_vs.spv";
  shader_info->path_spir_fs = "../media/shader/Scene/spir/shader_line_fs.spv";
  shader_info->with_recompilation = false;
  shader_info->with_depth_test = true;
  this->vec_shader_info.push_back(shader_info);

  //---------------------------
}

}
