#pragma once

#include <Loader/src/Import/Structure.h>
#include <Loader/src/Export/Structure.h>
#include <Loader/src/Transformation/Structure.h>
#include <Loader/src/Base/Exporter.h>
#include <string>


namespace ldr{

struct Structure{
  //---------------------------

  std::string get_current_path(){
    std::string format = (current_format != "-") ? "." + current_format : "";
    std::string filename = (current_name != "") ? current_name + format : current_name;
    std::string path = (filename != "") ? current_dir + "/" + filename : current_dir;
    return (path == "") ? "(not defined)" : path;
  }

  //General
  std::string current_dir = "";
  std::string current_name = "";
  std::string current_format = "ply";

  //Specific structure
  ldr::importer::Structure importer;
  ldr::exporter::Structure exporter;
  ldr::transformation::Structure transformation;

  //---------------------------
};

}
