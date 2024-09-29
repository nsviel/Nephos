#include "Module.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Utility/Function/File/File.h>


namespace vk::shader{

//Constructor / Destructor
Module::Module(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_file = new vk::shader::File(vk_struct);
  this->vk_compute = new vk::shader::Compute(vk_struct);
  this->vk_render = new vk::shader::Render(vk_struct);

  //---------------------------
}
Module::~Module(){}

//Main function
void Module::create_pipeline_module(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_file->recompile_shader(pipeline.shader);

  switch(pipeline.info.type){
    case vk::pipeline::RENDER:{
      vk_render->create_module(pipeline);
      break;
    }
    case vk::pipeline::COMPUTE:{
      vk_compute->create_module(pipeline);
      break;
    }
  }

  //---------------------------
}
void Module::clean_pipeline_module(vk::structure::Pipeline& pipeline){
  //---------------------------

  switch(pipeline.info.type){
    case vk::pipeline::RENDER:{
      vk_render->clean_module(pipeline);
      break;
    }
    case vk::pipeline::COMPUTE:{
      vk_compute->clean_module(pipeline);
      break;
    }
  }

  //---------------------------
}

}
