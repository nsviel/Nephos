#pragma once

#include <Utility/Specific/Common.h>


namespace utl::shader{

struct Info{
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

}
