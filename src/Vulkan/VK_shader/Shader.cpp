#include "Shader.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Utility/Function/File/File.h>


namespace vk::shader{

//Constructor / Destructor
Shader::Shader(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  this->path_output = "output.txt";
  utl::fct::file::clear_file(path_output);

  //---------------------------
}
Shader::~Shader(){}

//Main function
void Shader::create_pipeline_shader(vk::structure::Pipeline* pipeline){
  //---------------------------

  this->create_pipeline_shader_module(pipeline);
  this->create_pipeline_shader_info(pipeline);

  //---------------------------
}

//Subfunction
void Shader::create_pipeline_shader_module(vk::structure::Pipeline* pipeline){
  //---------------------------

  //Load spir format shaders
  this->recompile_shader(pipeline->definition.shader);
  auto code_vert = read_file(pipeline->definition.shader->path_spir_vs);
  auto code_frag = read_file(pipeline->definition.shader->path_spir_fs);

  //Create associated shader modules
  VkShaderModule module_vert = create_shader_module(code_vert);
  VkShaderModule module_frag = create_shader_module(code_frag);

  pair<VkShaderModule, VkShaderModule> shader_couple;
  shader_couple.first = module_vert;
  shader_couple.second = module_frag;
  pipeline->info.vec_shader_couple.push_back(shader_couple);

  //---------------------------
}
void Shader::create_pipeline_shader_info(vk::structure::Pipeline* pipeline){
  //---------------------------

  pair<VkShaderModule, VkShaderModule>& shader_couple = pipeline->info.vec_shader_couple[0];

  //Vertex shader link in pipeline
  VkPipelineShaderStageCreateInfo info_vert{};
  info_vert.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  info_vert.stage = TYP_SHADER_VS;
  info_vert.module = shader_couple.first;
  info_vert.pName = "main";
  info_vert.pSpecializationInfo = nullptr;

  //Fragment shader link in pipeline
  VkPipelineShaderStageCreateInfo info_frag{};
  info_frag.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  info_frag.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  info_frag.module = shader_couple.second;
  info_frag.pName = "main";
  info_frag.pSpecializationInfo = nullptr;

  //Shader info array
  pipeline->info.shader_stage.push_back(info_vert);
  pipeline->info.shader_stage.push_back(info_frag);

  //---------------------------
}
VkShaderModule Shader::create_shader_module(const std::vector<char>& code){
  //Shader modules are just a thin wrapper around the shader bytecode
  //---------------------------

  //Shader module info
  VkShaderModuleCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  create_info.codeSize = code.size();
  create_info.pCode = reinterpret_cast<const uint32_t*>(code.data());

  //Shader module creation
  VkShaderModule shaderModule;
  VkResult result = vkCreateShaderModule(struct_vulkan->device.device, &create_info, nullptr, &shaderModule);
  if (result != VK_SUCCESS) {
    throw std::runtime_error("[error] failed to create shader module!");
  }

  //---------------------------
  return shaderModule;
}

//Subfunction
std::vector<char> Shader::read_file(const std::string& path){
  std::ifstream file(path, std::ios::ate | std::ios::binary);
  //---------------------------

  if(!file.is_open()){
    throw std::runtime_error("[error] Shader file failed to open " + path);
  }

  size_t fileSize = (size_t) file.tellg();
  std::vector<char> buffer(fileSize);

  file.seekg(0);
  file.read(buffer.data(), fileSize);

  file.close();

  //---------------------------
  return buffer;
}
void Shader::recompile_shader(utl::base::Shader_info* shader_info){
  //---------------------------

  //Compile shader from GLSL to SPIR-V
  if(shader_info->compile_shader){
    this->run_recompilation(shader_info->path_glsl_vs, shader_info->path_spir_vs);
    this->run_recompilation(shader_info->path_glsl_fs, shader_info->path_spir_fs);
  }

  //---------------------------
}
void Shader::run_recompilation(string path_glsl, string path_spir){
  //---------------------------

  string command = "../src/Utility/Specific/compile.sh " + path_glsl + " " + path_spir + " >> " + path_output +" 2>&1";
  int result = system(command.c_str());
  if(result != 0){
    cout<<"[error] Shader compilation GLSL -> SPIR-V\n"<<command<<endl;
    exit(0);
  }

  //---------------------------
}

}
