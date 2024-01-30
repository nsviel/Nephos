#pragma once

#include <Utility/Specific/common.h>


namespace utl::shader{

class Base
{
public:
  //Contrustor / destructor
  Base();
  ~Base();

  utl::shader::Info* get_shader_info(string title);
  string get_glsl_path_vs(int ID_subclass);
  string get_glsl_path_fs(int ID_subclass);

  inline std::vector<utl::shader::Info*> get_vec_shader_info(){return vec_shader_info;}

protected:
  std::vector<utl::shader::Info*> vec_shader_info;
};

}
