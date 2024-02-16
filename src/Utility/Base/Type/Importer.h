#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Base/Media/File.h>


namespace utl::type{

struct Importer{
  //---------------------------

  virtual void import(std::string path){}
  virtual utl::media::File* import_data(std::string path){return nullptr;}

  utl::media::File* data_out;
  std::string format;

  //---------------------------
};

}
