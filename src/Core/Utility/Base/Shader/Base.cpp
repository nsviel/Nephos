#include "Base.h"

#include <iostream>


namespace utl::shader{

Base::Base(){
  //---------------------------

  //---------------------------
}
Base::~Base(){}

//Subfunction
utl::shader::Info* Base::get_shader_info(std::string name){
  //---------------------------

  for(int i=0; i<vec_shader_info.size(); i++){
    if(name == vec_shader_info[i]->name){
      return vec_shader_info[i];
    }
  }

  std::cout<<"[error] Didn't find shader info from name -> "<<name<<std::endl;

  //---------------------------
  return nullptr;
}
std::string Base::get_glsl_path_vs(int ID_subclass){
  //---------------------------

  std::string path_vs = vec_shader_info[ID_subclass]->path_glsl_vs;

  //---------------------------
  return path_vs;
}
std::string Base::get_glsl_path_fs(int ID_subclass){
  //---------------------------

  std::string path_fs = vec_shader_info[ID_subclass]->path_glsl_fs;

  //---------------------------
  return path_fs;
}

}
