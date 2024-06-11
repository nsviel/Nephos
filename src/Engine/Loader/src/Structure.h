#pragma once

#include <Loader/src/Base/Exporter.h>
#include <string>


namespace ldr{

struct Structure{
  //---------------------------

  std::string get_current_path(){
    std::string format = (current_format != "-") ? current_format : "";
    std::string filename = (current_name != "" && format != "") ? current_name + "." + format : "";
    std::string path = (filename != "") ? current_dir + "/" + filename : current_dir;
    return (path == "") ? "(not defined)" : path;
  }

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
