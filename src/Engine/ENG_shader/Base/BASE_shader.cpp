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
string BASE_shader::get_glsl_path_vs(int ID_subclass){
  //---------------------------

  string file_vs = vec_shader_info[ID_subclass]->path_vs;
  string folder = vec_shader_info[ID_subclass]->folder;
  string path_vs = "../src/Engine/ENG_shader/" + folder + "/glsl/" + file_vs + ".vert";

  //---------------------------
  return path_vs;
}
string BASE_shader::get_glsl_path_fs(int ID_subclass){
  //---------------------------

  string file_fs = vec_shader_info[ID_subclass]->path_fs;
  string folder = vec_shader_info[ID_subclass]->folder;
  string path_fs = "../src/Engine/ENG_shader/" + folder + "/glsl/" + file_fs + ".frag";

  //---------------------------
  return path_fs;
}
