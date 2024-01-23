#include "EDL.h"

#include <Engine/Engine.h>

#include <Utility/Namespace.h>


namespace eng::shader{

EDL::EDL(Engine* engine){
  //---------------------------

  util::Node* utility = engine->get_utility();
  camera::src::Node* node_camera = engine->get_node_camera();

  this->cam_manager = node_camera->get_camera_manager();
  this->utl_window = utility->get_utl_window();
  this->edl_param = new eng::shader::EDL_param();

  //---------------------------
  this->init_shader();
}
EDL::~EDL(){}

//Main function
void EDL::init_shader(){
  //---------------------------

  //Set parameter values
  edl_param->activated = true;
  edl_param->strength = 15.0;
  edl_param->radius = 1.0;

  //Add shader info
  Shader_info* shader_info = new Shader_info();
  shader_info->title = "EDL";
  shader_info->folder = "EDL";
  shader_info->path_glsl_vs = "../src/Engine/Render/Shader/EDL/glsl/shader_edl_vs.vert";
  shader_info->path_glsl_fs = "../src/Engine/Render/Shader/EDL/glsl/shader_edl_fs.frag";
  shader_info->path_spir_vs = "../src/Engine/Render/Shader/EDL/spir/shader_edl_vs.spv";
  shader_info->path_spir_fs = "../src/Engine/Render/Shader/EDL/spir/shader_edl_fs.spv";
  shader_info->compile_shader = true;
  shader_info->with_depth_test = true;
  shader_info->has_parameter = true;
  this->vec_shader_info.push_back(shader_info);

  //---------------------------
}
void EDL::update_shader(){
  entity::Camera* camera = cam_manager->get_current_camera();
  //---------------------------

  // Depth setup
  edl_param->z_near = camera->clip_near;
  edl_param->z_far = camera->clip_far;

  //Dimension
  vec2 window_dim = utl_window->get_window_dim();
  edl_param->tex_width = window_dim.x;
  edl_param->tex_height = window_dim.y;

  //---------------------------
}

}
