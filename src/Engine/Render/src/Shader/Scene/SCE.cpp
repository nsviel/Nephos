#include "SCE.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Render/Namespace.h>


namespace eng::shader{

SCE::SCE(eng::render::Node* node_render){
  //---------------------------

  utl::Node* node_utility = node_render->get_node_utility();

  this->utl_window = node_utility->get_utl_window();

  //---------------------------
  this->init_shader();
}
SCE::~SCE(){}

//Main function
void SCE::init_shader(){
  utl::shader::Info* shader_info;
  //---------------------------

  //Add shader info - Line
  shader_info = new utl::shader::Info();
  shader_info->title = "Line";
  shader_info->folder = "Scene";
  shader_info->path_glsl_vs = "../shader/Scene/glsl/shader_line_vs.vert";
  shader_info->path_glsl_fs = "../shader/Scene/glsl/shader_line_fs.frag";
  shader_info->path_spir_vs = "../shader/Scene/spir/shader_line_vs.spv";
  shader_info->path_spir_fs = "../shader/Scene/spir/shader_line_fs.spv";
  shader_info->compile_shader = false;
  shader_info->with_depth_test = true;
  this->vec_shader_info.push_back(shader_info);

  //Add shader info - Point
  shader_info = new utl::shader::Info();
  shader_info->title = "Point";
  shader_info->folder = "Scene";
  shader_info->path_glsl_vs = "../shader/Scene/glsl/shader_point_vs.vert";
  shader_info->path_glsl_fs = "../shader/Scene/glsl/shader_point_fs.frag";
  shader_info->path_spir_vs = "../shader/Scene/spir/shader_point_vs.spv";
  shader_info->path_spir_fs = "../shader/Scene/spir/shader_point_fs.spv";
  shader_info->compile_shader = false;
  shader_info->with_depth_test = true;
  this->vec_shader_info.push_back(shader_info);

  //Add shader info - Triangle
  shader_info = new utl::shader::Info();
  shader_info->title = "Triangle";
  shader_info->folder = "Scene";
  shader_info->path_glsl_vs = "../shader/Scene/glsl/shader_line_vs.vert";
  shader_info->path_glsl_fs = "../shader/Scene/glsl/shader_line_fs.frag";
  shader_info->path_spir_vs = "../shader/Scene/spir/shader_line_vs.spv";
  shader_info->path_spir_fs = "../shader/Scene/spir/shader_line_fs.spv";
  shader_info->compile_shader = false;
  shader_info->with_depth_test = true;
  this->vec_shader_info.push_back(shader_info);

  //---------------------------
}

}
