#pragma once

#include <Utility/Base/Data/Path.h>
#include <glm/glm.hpp>
#include <string>


namespace io::bookmark{

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
  int type = io::bookmark::FILE;
  utl::base::Path path;
  std::string size = "";
  std::string icon = "";
  glm::vec4 color_icon;
  glm::vec4 color_text;
  bool is_supressible = true;
  float weight = 0;

  //---------------------------
};

}
