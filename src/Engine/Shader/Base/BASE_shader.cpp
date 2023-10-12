#include "BASE_shader.h"


BASE_shader::BASE_shader(){
  //---------------------------

  //---------------------------
}
BASE_shader::~BASE_shader(){}

Shader_info* BASE_shader::get_shader_info(string title){
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
