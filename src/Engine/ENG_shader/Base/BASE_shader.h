#pragma once

#include <Utility/UTL_specific/common.h>

struct Shader_info{
  //---------------------------

  std::string title = "";
  std::string folder = "";
  std::string path_glsl_vs = "";
  std::string path_glsl_fs = "";
  std::string path_spir_vs = "";
  std::string path_spir_fs = "";

  bool compile_shader = false;
  bool with_depth_test = false;
  bool has_parameter = false;

  //---------------------------
};


class BASE_shader
{
public:
  //Contrustor / destructor
  BASE_shader();
  ~BASE_shader();

  Shader_info* get_shader_info(string title);
  string get_glsl_path_vs(int ID_subclass);
  string get_glsl_path_fs(int ID_subclass);

  inline std::vector<Shader_info*> get_vec_shader_info(){return vec_shader_info;}

protected:
  std::vector<Shader_info*> vec_shader_info;
};
