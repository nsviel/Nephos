#include "Pipeline.h"

#include <Vulkan/Namespace.h>


namespace vk::render::onscreen{

//Constructor / Destructor
Pipeline::Pipeline(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Pipeline::~Pipeline(){}

//Main function
void Pipeline::add_pipeline_triangle(vk::structure::Subpass* subpass){
  //---------------------------

  //Shader
  utl::shader::Info* shader_info = new utl::shader::Info();
  shader_info->name = "Canvas";
  shader_info->path_spir_vs = "../media/shader/Empty/spir/shader_empty_vs.spv";
  shader_info->path_spir_fs = "../media/shader/Empty/spir/shader_empty_fs.spv";
  shader_info->with_recompilation = false;
  shader_info->with_depth_test = false;

  //Pipeline
  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  pipeline->info.name = "triangle";
  pipeline->info.topology = utl::topology::TRIANGLE;
  pipeline->info.shader = shader_info;

  //---------------------------
  subpass->vec_pipeline.push_back(pipeline);
}

}
