#include "PSR_shader.h"

#include <Engine/Node/Engine.h>
#include <Utility/Node/Utility.h>
#include <Utility/UTL_window/UTL_window.h>


PSR_shader::PSR_shader(Engine* engine){
  //---------------------------

  Utility* utility = engine->get_utility();

  this->camera = engine->get_camera();
  this->utl_window = utility->get_utl_window();
  this->psr_param = new PSR_param();

  //---------------------------
  this->init_shader();
}
PSR_shader::~PSR_shader(){}

//Main function
void PSR_shader::init_shader(){
  //---------------------------

  Shader_info* shader_info = new Shader_info();
  shader_info->title = "PSR";
  shader_info->folder = "PSR";
  shader_info->path_spir_vs = "shader_edl_vs";
  shader_info->path_spir_fs = "shader_edl_fs";
  shader_info->compile_shader = true;
  shader_info->with_depth_test = true;
  this->vec_shader_info.push_back(shader_info);

  //---------------------------
}
void PSR_shader::update_shader(){
  //---------------------------

  // Depth setup
  psr_param->z_near = camera->clip_near;
  psr_param->z_far = camera->clip_far;

  //Dimension
  vec2 window_dim = utl_window->get_window_dim();
  psr_param->tex_width = window_dim.x;
  psr_param->tex_height = window_dim.y;

  //---------------------------
}
