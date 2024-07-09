#include "Shader.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Utility/Function/File/File.h>


namespace vk::pipeline{

//Constructor / Destructor
Shader::Shader(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_shader = new vk::shader::Shader(vk_struct);

  //---------------------------
}
Shader::~Shader(){}

//Main function
void Shader::create_pipeline_shader(vk::structure::Pipeline* pipeline){
  //---------------------------

  this->create_shader_module(pipeline);
  this->create_shader_info(pipeline);

  //---------------------------
}
void Shader::clean_pipeline_shader(vk::structure::Pipeline* pipeline){
  //---------------------------

  for(int i=0; i<pipeline->element.vec_shader.size(); i++){
    vk::pipeline::structure::Shader& shader = pipeline->element.vec_shader[i];

    vkDestroyShaderModule(vk_struct->device.handle, shader.vs, nullptr);
    vkDestroyShaderModule(vk_struct->device.handle, shader.fs, nullptr);
  }
  pipeline->element.vec_shader.clear();

  //---------------------------
}

//Subfunction
void Shader::create_shader_module(vk::structure::Pipeline* pipeline){
  //---------------------------

  //Load spir format shaders
  vk_shader->recompile_shader(pipeline->info.shader);
  auto code_vert = vk_shader->read_file(pipeline->info.shader->path_spir_vs);
  auto code_frag = vk_shader->read_file(pipeline->info.shader->path_spir_fs);

  //Create associated shader modules
  VkShaderModule module_vert = vk_shader->create_shader_module(code_vert);
  VkShaderModule module_frag = vk_shader->create_shader_module(code_frag);

  vk::pipeline::structure::Shader shader;
  shader.vs = module_vert;
  shader.fs = module_frag;
  pipeline->element.vec_shader.push_back(shader);

  //---------------------------
}
void Shader::create_shader_info(vk::structure::Pipeline* pipeline){
  //---------------------------

  vk::pipeline::structure::Shader& shader = pipeline->element.vec_shader[0];

  //Vertex shader link in pipeline
  VkPipelineShaderStageCreateInfo info_vert{};
  info_vert.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  info_vert.stage = TYP_SHADER_VS;
  info_vert.module = shader.vs;
  info_vert.pName = "main";
  info_vert.pSpecializationInfo = nullptr;

  //Fragment shader link in pipeline
  VkPipelineShaderStageCreateInfo info_frag{};
  info_frag.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  info_frag.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  info_frag.module = shader.fs;
  info_frag.pName = "main";
  info_frag.pSpecializationInfo = nullptr;

  //Shader info array
  pipeline->element.shader_stage.push_back(info_vert);
  pipeline->element.shader_stage.push_back(info_frag);

  //---------------------------
}

}
