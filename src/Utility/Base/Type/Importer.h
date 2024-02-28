#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Base/Media/File.h>


namespace utl::type{

struct Importer{
  //---------------------------

  virtual utl::file::Entity* import(std::string path){return nullptr;}

  utl::file::Entity* data = nullptr;
  std::string format = "";

  //---------------------------
};

}
