#pragma once

#include <Utility/Base/Data/Data.h>
#include <Utility/Base/Data/Pose.h>
#include <vector>
#include <string>


namespace io::exporter{

struct Configuration{
  //---------------------------

  std::string encoding = "";
  std::string path = "";
  glm::mat4 mat_model;
  glm::mat3 mat_rotation;
  bool with_colorization = false;
  int nb_vertex = 0;

  //---------------------------
};

}
