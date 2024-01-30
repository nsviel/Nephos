#include "Shader.h"


namespace utl::base{

Shader::Shader(){
  //---------------------------

  //---------------------------
}
Shader::~Shader(){}

utl::shader::Info* Shader::get_shader_info(string title){
  //---------------------------

  for(int i=0; i<vec_shader_info.size(); i++){
    if(title == vec_shader_info[i]->title){
      return vec_shader_info[i];
    }
  }

  std::cout<<"[error] Didn't find shader info from title "<<title<<std::endl;

  //---------------------------
  return nullptr;
}
string Shader::get_glsl_path_vs(int ID_subclass){
  //---------------------------

  string path_vs = vec_shader_info[ID_subclass]->path_glsl_vs;

  //---------------------------
  return path_vs;
}
string Shader::get_glsl_path_fs(int ID_subclass){
  //---------------------------

  string path_fs = vec_shader_info[ID_subclass]->path_glsl_fs;

  //---------------------------
  return path_fs;
}

}
