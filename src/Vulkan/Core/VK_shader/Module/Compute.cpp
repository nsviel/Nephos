#include "Compute.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Utility/Function/File/File.h>


namespace vk::shader{

//Constructor / Destructor
Compute::Compute(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_file = new vk::shader::File(vk_struct);

  //---------------------------
}
Compute::~Compute(){}

//Main function
void Compute::create_module(vk::structure::Pipeline& pipeline){
  //---------------------------

  this->create_shader_module(pipeline);
  this->create_shader_info(pipeline);

  //---------------------------
}
void Module::clean_module(vk::structure::Pipeline& pipeline){
  //---------------------------

  vkDestroyShaderModule(vk_struct->core.device.handle, pipeline.shader.module.comp, nullptr);

  //---------------------------
}

//Subfunction
void Compute::create_shader_module(vk::structure::Pipeline& pipeline){
  vk::shader::structure::Info& shader_info = pipeline.shader.info;
  //---------------------------

  //Load spir format shaders
  auto code_comp = vk_file->read_file(pipeline.shader.info.path_spir.comp);

  //Create associated shader modules
  pipeline.shader.module.comp = build_module(code_comp);

  //---------------------------
}
void Compute::create_shader_info(vk::structure::Pipeline& pipeline){
  pipeline.component.vec_shader_stage.clear();
  //---------------------------

  VkPipelineShaderStageCreateInfo info_comp{};
  info_comp.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  info_comp.stage = VK_SHADER_STAGE_COMPUTE_BIT;
  info_comp.module = pipeline.shader.module.comp;
  info_comp.pName = "main";
  info_comp.pSpecializationInfo = nullptr;
  pipeline.component.vec_shader_stage.push_back(info_comp);

  //---------------------------
}
VkShaderModule Compute::build_module(const std::vector<char>& code){
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
