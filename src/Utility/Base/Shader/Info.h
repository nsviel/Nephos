#pragma once

#include <string>


namespace utl::shader{

struct Path_shader{
  //---------------------------

  std::string vs = "";
  std::string fs = "";

  //---------------------------
};

struct Info{
  //---------------------------

  //Configuration
  std::string name = "";
  bool with_recompilation = false;
  bool with_depth_test = false;

  //Path
  utl::shader::Path_shader path_glsl;
  utl::shader::Path_shader path_spir;
  
  //---------------------------
};

}
