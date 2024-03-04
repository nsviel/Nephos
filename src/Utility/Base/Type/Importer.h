#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Base/Media/File.h>


namespace utl::type{

struct Importer{
  //---------------------------

  virtual utl::file::Data* import(std::string path){return nullptr;}
  virtual utl::file::Data* import(utl::file::Data* file){return nullptr;}

  utl::file::Data* data = nullptr;
  std::string format = "";

  //---------------------------
};

}
