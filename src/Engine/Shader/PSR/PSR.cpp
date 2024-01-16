#include "PSR.h"

#include <Engine/Engine.h>
#include <Utility/Namespace.h>


namespace eng::shader{

PSR::PSR(Engine* engine){
  //---------------------------

  util::Node* utility = engine->get_utility();
  eng::camera::Node* node_camera = engine->get_node_camera();

  this->cam_manager = node_camera->get_camera_manager();
  this->utl_window = utility->get_utl_window();
  this->psr_param = new PSR_param();

  //---------------------------
  this->init_shader();
}
PSR::~PSR(){}

//Main function
void PSR::init_shader(){
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
void PSR::update_shader(){
  eng::base::Camera* camera = cam_manager->get_current_camera();
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

}
