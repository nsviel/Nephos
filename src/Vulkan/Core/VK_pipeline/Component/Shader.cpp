#include "Shader.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Utility/Function/File/File.h>


namespace vk::pipeline{

//Constructor / Destructor
Shader::Shader(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_file = new vk::shader::File(vk_struct);

  //---------------------------
}
Shader::~Shader(){}

//Main function
void Shader::create_pipeline_shader(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_file->recompile_shader(pipeline.shader);
  this->create_shader_module(pipeline);
  this->create_shader_info(pipeline);

  //---------------------------
}
void Shader::clean_pipeline_shader(vk::structure::Pipeline& pipeline){
  //---------------------------

  vkDestroyShaderModule(vk_struct->core.device.handle, pipeline.shader.module.vs, nullptr);
  vkDestroyShaderModule(vk_struct->core.device.handle, pipeline.shader.module.fs, nullptr);

  //---------------------------
}

//Subfunction
void Shader::create_shader_module(vk::structure::Pipeline& pipeline){
  //---------------------------

  //Load spir format shaders
  auto code_vert = vk_file->read_file(pipeline.shader.info.path_spir.vs);
  auto code_frag = vk_file->read_file(pipeline.shader.info.path_spir.fs);

  //Create associated shader modules
  pipeline.shader.module.vs = create_module(code_vert);
  pipeline.shader.module.fs = create_module(code_frag);

  //---------------------------
}
void Shader::create_shader_info(vk::structure::Pipeline& pipeline){
  pipeline.component.vec_shader_stage.clear();
  //---------------------------

  //Vertex shader link in pipeline
  VkPipelineShaderStageCreateInfo info_vert{};
  info_vert.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  info_vert.stage = VK_SHADER_STAGE_VERTEX_BIT;
  info_vert.module = pipeline.shader.module.vs;
  info_vert.pName = "main";
  info_vert.pSpecializationInfo = nullptr;
  pipeline.component.vec_shader_stage.push_back(info_vert);

  //Fragment shader link in pipeline
  VkPipelineShaderStageCreateInfo info_frag{};
  info_frag.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  info_frag.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  info_frag.module = pipeline.shader.module.fs;
  info_frag.pName = "main";
  info_frag.pSpecializationInfo = nullptr;
  pipeline.component.vec_shader_stage.push_back(info_frag);

  //---------------------------
}
VkShaderModule Shader::create_module(const std::vector<char>& code){
  //Shader modules are just a thin wrapper around the shader bytecode
  //---------------------------

  //Shader module info
  VkShaderModuleCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  create_info.codeSize = code.size();
  create_info.pCode = reinterpret_cast<const uint32_t*>(code.data());

  //Shader module creation
  VkShaderModule module;
  VkResult result = vkCreateShaderModule(vk_struct->core.device.handle, &create_info, nullptr, &module);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create shader module!");
  }

  //---------------------------
  return module;
}

}