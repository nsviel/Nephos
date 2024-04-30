#pragma once

#include <imgui/core/imgui.h>
#include <glm/glm.hpp>
#include <string>


namespace ldr::item{

enum ColumnID{
  NAME,
  WEIGHT,
  FORMAT
};

enum type{
  FOLDER = 0,
  FILE = 1,
};

}

namespace ldr{

struct Item{
  //---------------------------

  //Item stuff
  int ID = -1;
  int type = ldr::item::FILE;
  std::string path = "";
  std::string name = "";
  std::string format = "";
  std::string size = "";
  std::string icon = "";
  glm::vec4 color_icon;
  glm::vec4 color_text;
  bool is_supressible = true;
  float weight = 0;

  //---------------------------
};

}
