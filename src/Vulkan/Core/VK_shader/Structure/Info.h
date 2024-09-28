#pragma once

#include <string>


namespace vk::shader::structure{

struct Path{
  //---------------------------

  std::string vs = "";
  std::string fs = "";
  std::string comp = "";

  //---------------------------
};

struct Info{
  //---------------------------

  //Configuration
  std::string name = "";
  bool with_recompilation = false;
  bool with_depth_test = false;

  //Path
  vk::shader::structure::Path path_glsl;
  vk::shader::structure::Path path_spir;

  //---------------------------
};

}
