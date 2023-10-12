#include "CAN_shader.h"

#include <Engine.h>
#include <Window/Window.h>


CAN_shader::CAN_shader(Engine* engine){
  //---------------------------

  this->window = engine->get_window();

  //---------------------------
  this->init_shader();
}
CAN_shader::~CAN_shader(){}

//Main function
void CAN_shader::init_shader(){
  //---------------------------

  Shader_info* shader_info = new Shader_info();
  shader_info->title = "Canvas";
  shader_info->folder = "Canvas";
  shader_info->path_vs = "shader_canvas_empty_vs";
  shader_info->path_fs = "shader_canvas_empty_fs";
  shader_info->compile_shader = true;
  shader_info->with_depth_test = false;
  this->vec_shader_info.push_back(shader_info);

  //---------------------------
}
