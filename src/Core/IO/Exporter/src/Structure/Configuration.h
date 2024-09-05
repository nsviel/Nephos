#pragma once

#include <Exporter/src/Structure/Enum.h>
#include <Utility/Base/Data/Data.h>
#include <Utility/Base/Data/Pose.h>
#include <vector>
#include <string>


namespace io::exp{

struct Configuration{
  //---------------------------

  io::exp::Encoding encoding = io::exp::BINARY;
  std::vector<io::exp::Field> vec_property;
  std::string format = "";
  std::string path = "";
  glm::mat4 mat_model;
  glm::mat3 mat_rotation;
  bool with_transformation = false;
  bool with_colorization = false;
  int nb_property = 0;
  int nb_vertex = 0;

  //---------------------------
};

}
