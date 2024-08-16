#pragma once

#include <Utility/Base/Shader/Info.h>
#include <vector>
#include <string>


namespace utl::shader{

class Base
{
public:
  //Contrustor / destructor
  Base();
  ~Base();

public:
  //Main function
  virtual void build_shader_info(){}

  //Subfunction
  utl::shader::Info* get_shader_info(std::string name);
  std::string get_glsl_path_vs(int ID_subclass);
  std::string get_glsl_path_fs(int ID_subclass);

  inline std::vector<utl::shader::Info*> get_vec_shader_info(){return vec_shader_info;}

protected:
  std::vector<utl::shader::Info*> vec_shader_info;
};

}
