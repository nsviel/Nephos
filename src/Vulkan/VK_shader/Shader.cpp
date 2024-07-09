#include "Shader.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Utility/Function/File/File.h>


namespace vk::shader{

//Constructor / Destructor
Shader::Shader(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  this->path_output = "output.txt";
  utl::file::clear(path_output);

  //---------------------------
}
Shader::~Shader(){}

//Main function
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
  VkResult result = vkCreateShaderModule(vk_struct->device.handle, &create_info, nullptr, &shaderModule);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create shader module!");
  }

  //---------------------------
  return shaderModule;
}
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
void Shader::recompile_shader(utl::shader::Info* shader_info){
  //---------------------------

  //Compile shader from GLSL to SPIR-V
  if(shader_info->compile_shader){
    this->run_recompilation(shader_info->path_glsl_vs, shader_info->path_spir_vs);
    this->run_recompilation(shader_info->path_glsl_fs, shader_info->path_spir_fs);
  }

  //---------------------------
}
void Shader::run_recompilation(std::string path_glsl, std::string path_spir){
  //---------------------------

  std::string command = "../src/Utility/Specific/Compile.sh " + path_glsl + " " + path_spir + " >> " + path_output +" 2>&1";
  int result = system(command.c_str());
  if(result != 0){
    std::cout<<"[error] Shader compilation GLSL -> SPIR-V\n"<<command<<std::endl;
    exit(0);
  }

  //---------------------------
}

}
