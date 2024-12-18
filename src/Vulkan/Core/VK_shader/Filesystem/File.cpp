#include "File.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Utility/Function/File/File.h>


namespace vk::shader{

//Constructor / Destructor
File::File(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

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
void File::recompile_shader(vk::shader::structure::Shader& shader){
  //---------------------------

  //Compile shader from GLSL to SPIR-V
  if(shader.info.with_recompilation){
    this->run_recompilation(shader.info.path_glsl.vs, shader.info.path_spir.vs);
    this->run_recompilation(shader.info.path_glsl.fs, shader.info.path_spir.fs);
    this->run_recompilation(shader.info.path_glsl.comp, shader.info.path_spir.comp);
  }

  //---------------------------
}
void File::run_recompilation(std::string path_glsl, std::string path_spir){
  if(path_glsl == "" || path_spir == "") return;
  //---------------------------

  std::string command = "glslc " + path_glsl + " -o " + path_spir;
  int result = system(command.c_str());
  if(result != 0){
    std::cout<<"[error] failed shader compilation GLSL / SPIR-V"<<std::endl;
    exit(0);
  }

  //---------------------------
}

}
