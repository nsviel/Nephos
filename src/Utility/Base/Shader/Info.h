#pragma once

#include <string>


namespace utl::shader{

struct Info{
  //---------------------------

  std::string title = "";
  std::string folder = "";

  std::string path_glsl_vs = "";
  std::string path_glsl_fs = "";
  std::string path_spir_vs = "";
  std::string path_spir_fs = "";

  bool with_recompilation = false;
  bool with_depth_test = false;

  //---------------------------
};

}
