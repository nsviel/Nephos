#pragma once

#include <glm/glm.hpp>
#include <string>


namespace ldr::bookmark{

enum ColumnID{
  NAME,
  WEIGHT,
  FORMAT
};

enum type{
  FOLDER = 0,
  FILE = 1,
};

struct Item{
  //---------------------------

  //Item stuff
  int ID = -1;
  int type = ldr::bookmark::FILE;
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
