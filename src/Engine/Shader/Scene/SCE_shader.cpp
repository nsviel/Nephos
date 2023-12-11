#include "SCE_shader.h"

#include <Engine/Node/Engine.h>
#include <Utility/Node/Namespace.h>
#include <Utility/Element/UTL_window.h>


SCE_shader::SCE_shader(Engine* engine){
  //---------------------------

  utility::Node* utility = engine->get_utility();

  this->utl_window = utility->get_utl_window();

  //---------------------------
  this->init_shader();
}
SCE_shader::~SCE_shader(){}

//Main function
void SCE_shader::init_shader(){
  Shader_info* shader_info;
  //---------------------------

  //Add shader info - Line
  shader_info = new Shader_info();
  shader_info->title = "Line";
  shader_info->folder = "Scene";
  shader_info->path_glsl_vs = "../src/Engine/Shader/Scene/glsl/shader_line_vs.vert";
  shader_info->path_glsl_fs = "../src/Engine/Shader/Scene/glsl/shader_line_fs.frag";
  shader_info->path_spir_vs = "../src/Engine/Shader/Scene/spir/shader_line_vs.spv";
  shader_info->path_spir_fs = "../src/Engine/Shader/Scene/spir/shader_line_fs.spv";
  shader_info->compile_shader = true;
  shader_info->with_depth_test = true;
  this->vec_shader_info.push_back(shader_info);

  //Add shader info - Point
  shader_info = new Shader_info();
  shader_info->title = "Point";
  shader_info->folder = "Scene";
  shader_info->path_glsl_vs = "../src/Engine/Shader/Scene/glsl/shader_point_vs.vert";
  shader_info->path_glsl_fs = "../src/Engine/Shader/Scene/glsl/shader_point_fs.frag";
  shader_info->path_spir_vs = "../src/Engine/Shader/Scene/spir/shader_point_vs.spv";
  shader_info->path_spir_fs = "../src/Engine/Shader/Scene/spir/shader_point_fs.spv";
  shader_info->compile_shader = true;
  shader_info->with_depth_test = true;
  this->vec_shader_info.push_back(shader_info);

  //---------------------------
}
