#ifndef BASE_SHADER_H
#define BASE_SHADER_H

#include <Specific/common.h>

struct Shader_info{
  //---------------------------

  std::string title = "";
  std::string folder = "";
  std::string path_vs = "";
  std::string path_fs = "";

  bool compile_shader = false;
  bool with_depth_test = false;

  //---------------------------
};


class BASE_shader
{
public:
  //Contrustor / destructor
  BASE_shader();
  ~BASE_shader();

  Shader_info* get_shader_info(string title);

  inline std::vector<Shader_info*> get_vec_shader_info(){return vec_shader_info;}

protected:
  std::vector<Shader_info*> vec_shader_info;
};

#endif
