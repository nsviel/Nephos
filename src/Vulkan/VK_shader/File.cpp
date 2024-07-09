#include "File.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Utility/Function/File/File.h>


namespace vk::shader{

//Constructor / Destructor
File::File(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  this->path_output = "output.txt";
  utl::file::clear(path_output);

  //---------------------------
}
File::~File(){}

//Main function
std::vector<char> File::read_file(const std::string& path){
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
void File::recompile_shader(utl::shader::Info* shader_info){
  //---------------------------

  //Compile shader from GLSL to SPIR-V
  if(shader_info->compile_shader){
    this->run_recompilation(shader_info->path_glsl_vs, shader_info->path_spir_vs);
    this->run_recompilation(shader_info->path_glsl_fs, shader_info->path_spir_fs);
  }

  //---------------------------
}
void File::run_recompilation(std::string path_glsl, std::string path_spir){
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
