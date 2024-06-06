#pragma once

#include <Loader/src/Base/Exporter.h>
#include <string>


namespace ldr{

struct Structure{
  //---------------------------

  //General
  std::string current_dir = "";
  std::string current_name = "";
  std::string current_format = "ply";

  //Import
  float import_scaling = 1;
  bool import_center = false;
  bool import_remove_old = true;

  //Export
  int export_encoding = ldr::io::BINARY;

  //---------------------------
};

}
