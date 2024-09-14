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
void Shader::create_pipeline_shader(vk::structure::Pipeline* pipeline){
  //---------------------------

  this->create_shader_module(pipeline);
  this->create_shader_info(pipeline);

  //---------------------------
}
void Shader::clean_pipeline_shader(){
  //---------------------------

  for(int i=0; i<vec_shader.size(); i++){
    vk::pipeline::structure::Shader& shader = vec_shader[i];

    vkDestroyShaderModule(vk_struct->device.handle, shader.vs, nullptr);
    vkDestroyShaderModule(vk_struct->device.handle, shader.fs, nullptr);
  }
  vec_shader.clear();

  //---------------------------
}

//Subfunction
void Shader::create_shader_module(vk::structure::Pipeline* pipeline){
  //---------------------------

  //Load spir format shaders
  vk_file->recompile_shader(pipeline->info.shader);
  auto code_vert = vk_file->read_file(pipeline->info.shader->path_spir_vs);
  auto code_frag = vk_file->read_file(pipeline->info.shader->path_spir_fs);

  //Create associated shader modules
  VkShaderModule module_vert = create_module(code_vert);
  VkShaderModule module_frag = create_module(code_frag);

  vk::pipeline::structure::Shader shader;
  shader.vs = module_vert;
  shader.fs = module_frag;
  vec_shader.push_back(shader);

  //---------------------------
}
void Shader::create_shader_info(vk::structure::Pipeline* pipeline){
  //---------------------------

  for(int i=0; i<vec_shader.size(); i++){
    vk::pipeline::structure::Shader& shader = vec_shader[i];

    //Vertex shader link in pipeline
    VkPipelineShaderStageCreateInfo info_vert{};
    info_vert.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    info_vert.stage = VK_SHADER_STAGE_VERTEX_BIT;
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
    pipeline->element.vec_shader_stage.push_back(info_vert);
    pipeline->element.vec_shader_stage.push_back(info_frag);
  }

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
  VkShaderModule shaderModule;
  VkResult result = vkCreateShaderModule(vk_struct->device.handle, &create_info, nullptr, &shaderModule);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create shader module!");
  }

  //---------------------------
  return shaderModule;
}

}
