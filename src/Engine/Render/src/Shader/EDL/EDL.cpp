#include "EDL.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Camera/Namespace.h>
#include <Render/Namespace.h>


namespace eng::shader{

EDL::EDL(eng::render::Node* node_render){
  //---------------------------

  utl::Node* utility = node_render->get_node_utility();
  eng::cam::Node* node_camera = node_render->get_node_camera();

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
  utl::shader::Info* shader_info = new utl::shader::Info();
  shader_info->title = "EDL";
  shader_info->folder = "EDL";
  shader_info->path_glsl_vs = "../shader/EDL/glsl/shader_edl_vs.vert";
  shader_info->path_glsl_fs = "../shader/EDL/glsl/shader_edl_fs.frag";
  shader_info->path_spir_vs = "../shader/EDL/spir/shader_edl_vs.spv";
  shader_info->path_spir_fs = "../shader/EDL/spir/shader_edl_fs.spv";
  shader_info->compile_shader = false;
  shader_info->with_depth_test = true;
  shader_info->has_parameter = true;
  this->vec_shader_info.push_back(shader_info);

  //---------------------------
}
void EDL::update_shader(){
  utl::entity::Camera* camera = cam_manager->get_current_camera();
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
