#include "SCE.h"

#include <Engine/Node.h>
#include <Engine/Render/Namespace.h>
#include <Utility/Namespace.h>


namespace eng::shader{

SCE::SCE(eng::render::Node* node_render){
  //---------------------------

  eng::Node* engine = node_render->get_engine();
  utl::Node* utility = engine->get_node_utility();

  this->utl_window = utility->get_utl_window();

  //---------------------------
  this->init_shader();
}
SCE::~SCE(){}

//Main function
void SCE::init_shader(){
  utl::base::Shader_info* shader_info;
  //---------------------------

  //Add shader info - Line
  shader_info = new utl::base::Shader_info();
  shader_info->title = "Line";
  shader_info->folder = "Scene";
  shader_info->path_glsl_vs = "../src/Engine/Render/src/Shader/Scene/glsl/shader_line_vs.vert";
  shader_info->path_glsl_fs = "../src/Engine/Render/src/Shader/Scene/glsl/shader_line_fs.frag";
  shader_info->path_spir_vs = "../src/Engine/Render/src/Shader/Scene/spir/shader_line_vs.spv";
  shader_info->path_spir_fs = "../src/Engine/Render/src/Shader/Scene/spir/shader_line_fs.spv";
  shader_info->compile_shader = true;
  shader_info->with_depth_test = true;
  this->vec_shader_info.push_back(shader_info);

  //Add shader info - Point
  shader_info = new utl::base::Shader_info();
  shader_info->title = "Point";
  shader_info->folder = "Scene";
  shader_info->path_glsl_vs = "../src/Engine/Render/src/Shader/Scene/glsl/shader_point_vs.vert";
  shader_info->path_glsl_fs = "../src/Engine/Render/src/Shader/Scene/glsl/shader_point_fs.frag";
  shader_info->path_spir_vs = "../src/Engine/Render/src/Shader/Scene/spir/shader_point_vs.spv";
  shader_info->path_spir_fs = "../src/Engine/Render/src/Shader/Scene/spir/shader_point_fs.spv";
  shader_info->compile_shader = true;
  shader_info->with_depth_test = true;
  this->vec_shader_info.push_back(shader_info);

  //Add shader info - Triangle
  shader_info = new utl::base::Shader_info();
  shader_info->title = "Triangle";
  shader_info->folder = "Scene";
  shader_info->path_glsl_vs = "../src/Engine/Render/src/Shader/Scene/glsl/shader_line_vs.vert";
  shader_info->path_glsl_fs = "../src/Engine/Render/src/Shader/Scene/glsl/shader_line_fs.frag";
  shader_info->path_spir_vs = "../src/Engine/Render/src/Shader/Scene/spir/shader_line_vs.spv";
  shader_info->path_spir_fs = "../src/Engine/Render/src/Shader/Scene/spir/shader_line_fs.spv";
  shader_info->compile_shader = true;
  shader_info->with_depth_test = true;
  this->vec_shader_info.push_back(shader_info);

  //---------------------------
}

}
