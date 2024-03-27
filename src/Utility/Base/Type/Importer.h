#pragma once

#include <Utility/Specific/Common.h>
#include <Utility/Base/Media/File.h>


namespace utl::type{

struct Importer{
  //---------------------------

  virtual utl::file::Data* import(utl::file::Path path){return nullptr;}

  utl::file::Data* data = nullptr;
  std::string format = "";
  bool require_discrete_gpu = false;

  //---------------------------
};

}
