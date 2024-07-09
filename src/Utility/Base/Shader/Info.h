#pragma once

#include <string>


namespace utl::shader{

struct Info{
  //---------------------------

  //Configuration
  std::string title = "";
  bool with_recompilation = false;
  bool with_depth_test = false;

  //Path
  std::string path_glsl_vs = "";
  std::string path_glsl_fs = "";
  std::string path_spir_vs = "";
  std::string path_spir_fs = "";

  //---------------------------
};

}
