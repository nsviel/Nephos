#include "EDL_shader.h"

#include <Engine.h>
#include <Param.h>
#include <ELE_window/Window.h>


EDL_shader::EDL_shader(Engine* engine){
  //---------------------------

  this->param = engine->get_param();
  this->window = engine->get_window();
  this->edl_param = new EDL_param();

  //---------------------------
  this->init_shader();
}
EDL_shader::~EDL_shader(){}

//Main function
void EDL_shader::init_shader(){
  //---------------------------

  //Set parameter values
  edl_param->activated = true;
  edl_param->strength = 15.0;
  edl_param->radius = 1.0;

  //Add shader info
  Shader_info* shader_info = new Shader_info();
  shader_info->title = "EDL";
  shader_info->folder = "EDL";
  shader_info->path_vs = "shader_edl_vs";
  shader_info->path_fs = "shader_edl_fs";
  shader_info->compile_shader = true;
  shader_info->with_depth_test = true;
  shader_info->has_parameter = true;
  this->vec_shader_info.push_back(shader_info);

  //---------------------------
}
void EDL_shader::update_shader(){
  Struct_camera* camera = &param->camera;
  //---------------------------

  // Depth setup
  edl_param->z_near = camera->clip_near;
  edl_param->z_far = camera->clip_far;

  //Dimension
  vec2 window_dim = window->get_window_dim();
  edl_param->tex_width = window_dim.x;
  edl_param->tex_height = window_dim.y;

  //---------------------------
}
