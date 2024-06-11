#pragma once

#include <string>
#include <vector>


namespace rad::model::sphere::structure{

struct Sphere{
  //---------------------------

  std::string get_current_path(){
    std::string path = dir+ "/" + mode + "_" + filename;
    return path;
  }

  //General
  std::string mode = "NFOV";
  std::string filename = "sphere.data";
  std::string dir = "../media/calibration";

  //Data
  std::vector<glm::vec3> data;
  int size = 0;

  //R
  glm::vec2 R_range = glm::vec2(0, 0);
  float R_resolution = 0;
  int R_size = 0;

  //It
  glm::vec2 It_range = glm::vec2(0, 0);
  float It_resolution = 0;
  int It_size = 0;

  //I
  glm::vec2 I_range = glm::vec2(0, 0);

  //---------------------------
};

}
