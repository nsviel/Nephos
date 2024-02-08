#include "SCE.h"

#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::render{

SCE::SCE(vk::Node* node_vulkan){
  //---------------------------


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
  shader_info->path_glsl_vs = "../src/Engine/Render/src/Shader/Scene/glsl/shader_line_vs.vert";
  shader_info->path_glsl_fs = "../src/Engine/Render/src/Shader/Scene/glsl/shader_line_fs.frag";
  shader_info->path_spir_vs = "../src/Engine/Render/src/Shader/Scene/spir/shader_line_vs.spv";
  shader_info->path_spir_fs = "../src/Engine/Render/src/Shader/Scene/spir/shader_line_fs.spv";
  shader_info->compile_shader = true;
  shader_info->with_depth_test = true;
  this->vec_shader_info.push_back(shader_info);

  //Add shader info - Point
  shader_info = new utl::shader::Info();
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
  shader_info = new utl::shader::Info();
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
