#pragma once

#include <string>


namespace vk::shader{

struct Path{
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
  vk::shader::Path path_glsl;
  vk::shader::Path path_spir;

  //---------------------------
};

}
