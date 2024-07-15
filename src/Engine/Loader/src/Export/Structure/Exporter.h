#pragma once

#include <Utility/Base/Data/Data.h>
#include <Utility/Base/Data/Pose.h>
#include <vector>
#include <string>


namespace ldr::exporter{

enum Mode{
  EXPORT = 0,
  RECORD = 1,
};

enum Encoding{
  ASCII = 0,
  BINARY = 1,
};

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

struct Base{
  //---------------------------

  virtual void export_data(ldr::exporter::Configuration& config, utl::base::Data* data){}
  virtual void export_ascii(utl::base::Data* data, glm::mat4 mat, std::string path){}
  virtual void export_binary(utl::base::Data* data, glm::mat4 mat, std::string path){}

  std::vector<ldr::exporter::Encoding> vec_encoding;
  std::string format = "";
  bool use_rgba = true;

  //---------------------------
};

}
