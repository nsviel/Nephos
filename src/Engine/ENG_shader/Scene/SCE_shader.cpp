#include "SCE_shader.h"

#include <Engine.h>
#include <ELE_window/ELE_window.h>


SCE_shader::SCE_shader(Engine* engine){
  //---------------------------

  this->ele_window = engine->get_ele_window();

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
  shader_info->path_glsl_vs = "../src/Engine/ENG_shader/Scene/glsl/shader_line_vs.frag";
  shader_info->path_glsl_fs = "../src/Engine/ENG_shader/Scene/glsl/shader_line_fs.vert";
  shader_info->path_spir_vs = "../src/Engine/ENG_shader/Scene/spir/shader_line_vs.spv";
  shader_info->path_spir_fs = "../src/Engine/ENG_shader/Scene/spir/shader_line_fs.spv";
  shader_info->compile_shader = true;
  shader_info->with_depth_test = true;
  this->vec_shader_info.push_back(shader_info);

  //Add shader info - Point
  shader_info = new Shader_info();
  shader_info->title = "Point";
  shader_info->folder = "Scene";
  shader_info->path_glsl_vs = "../src/Engine/ENG_shader/Scene/glsl/shader_point_vs.frag";
  shader_info->path_glsl_fs = "../src/Engine/ENG_shader/Scene/glsl/shader_point_fs.vert";
  shader_info->path_spir_vs = "../src/Engine/ENG_shader/Scene/spir/shader_point_vs.spv";
  shader_info->path_spir_fs = "../src/Engine/ENG_shader/Scene/spir/shader_point_fs.spv";
  shader_info->compile_shader = true;
  shader_info->with_depth_test = true;
  this->vec_shader_info.push_back(shader_info);

  //---------------------------
}
