#include "Module.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Utility/Function/File/File.h>


namespace vk::pipeline{

//Constructor / Destructor
Module::Module(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_file = new vk::shader::File(vk_struct);

  //---------------------------
}
Module::~Module(){}

//Main function
void Module::create_pipeline_shader(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_file->recompile_shader(pipeline.shader);

  if(pipeline.info.type = vk::pipeline::RENDER){

  }
this->create_render_module(pipeline);
  this->create_shader_info(pipeline);

  //---------------------------
}
void Module::clean_pipeline_shader(vk::structure::Pipeline& pipeline){
  //---------------------------

  vkDestroyShaderModule(vk_struct->core.device.handle, pipeline.shader.module.vs, nullptr);
  vkDestroyShaderModule(vk_struct->core.device.handle, pipeline.shader.module.fs, nullptr);

  //---------------------------
}

}
