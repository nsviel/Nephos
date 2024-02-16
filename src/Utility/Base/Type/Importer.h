#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Base/Media/File.h>


namespace utl::type{

struct Importer{
  //---------------------------

  virtual utl::media::File* import(std::string path){return nullptr;}

  utl::media::File* data = nullptr;
  std::string format = "";

  //---------------------------
};

}
