#include "Canvas.h"

#include <Vulkan/Namespace.h>


namespace vk::render::pipeline{

//Constructor / Destructor
Canvas::Canvas(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Canvas::~Canvas(){}

//Main function
void Canvas::add_pipeline(vk::structure::Subpass& subpass){
  //---------------------------

  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  this->set_pipeline(*pipeline);
  this->set_shader(*pipeline);
  this->set_binding(*pipeline);

  //---------------------------
  subpass.map_pipeline["triangle"] = pipeline;
}

//Subfunction
void Canvas::set_pipeline(vk::structure::Pipeline& pipeline){
  //---------------------------

  pipeline.info.topology = utl::topology::TRIANGLE;

  //---------------------------
}
void Canvas::set_shader(vk::structure::Pipeline& pipeline){
  //---------------------------

  utl::shader::Info* shader_info = new utl::shader::Info();
  shader_info->name = "Canvas";
  shader_info->path_spir_vs = "../media/shader/Canvas/spir/canvas_vs.spv";
  shader_info->path_spir_fs = "../media/shader/Canvas/spir/canvas_fs.spv";
  shader_info->with_recompilation = true;
  shader_info->with_depth_test = false;

  //---------------------------
  pipeline.info.shader = shader_info;
}
void Canvas::set_binding(vk::structure::Pipeline& pipeline){
  //---------------------------


  //---------------------------
}

}
