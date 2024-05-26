#pragma once

#include <Utility/Base/Media/File.h>
#include <Data/src/Base/Entity.h>
#include <Data/src/Base/Set.h>
#include <string>

namespace dat::base{class Object;}


namespace ldr::base{

struct Importer{
  //---------------------------

  virtual utl::media::File* import(utl::media::Path path){return nullptr;}

  utl::file::Data* data = nullptr;
  std::string format = "";
  bool require_discrete_gpu = false;

  //---------------------------
};

}
