#pragma once

#include <IO/src/Export/Structure/Enum.h>
#include <IO/src/Export/Structure/Configuration.h>
#include <Utility/Base/Data/Data.h>
#include <vector>
#include <string>


namespace ldr::exporter{

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
