#include "EDL.h"

#include <Engine/Node/Engine.h>
#include <Engine/Base/Namespace.h>
#include <Utility/Node/Namespace.h>


namespace eng::shader{

EDL::EDL(Engine* engine){
  //---------------------------

  utility::Node* utility = engine->get_utility();

  this->camera = engine->get_camera();
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
  shader_info->path_glsl_vs = "../src/Engine/Shader/EDL/glsl/shader_edl_vs.vert";
  shader_info->path_glsl_fs = "../src/Engine/Shader/EDL/glsl/shader_edl_fs.frag";
  shader_info->path_spir_vs = "../src/Engine/Shader/EDL/spir/shader_edl_vs.spv";
  shader_info->path_spir_fs = "../src/Engine/Shader/EDL/spir/shader_edl_fs.spv";
  shader_info->compile_shader = true;
  shader_info->with_depth_test = true;
  shader_info->has_parameter = true;
  this->vec_shader_info.push_back(shader_info);

  //---------------------------
}
void EDL::update_shader(){
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
