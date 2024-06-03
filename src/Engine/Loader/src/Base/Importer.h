#pragma once

#include <Data/src/Base/Entity.h>
#include <Data/src/Base/Set.h>
#include <string>

namespace dat::base{class Object;}


namespace ldr::base{

struct Importer{
  //---------------------------

  virtual utl::base::Element* import(utl::media::Path path){return nullptr;}

  std::string format = "";
  bool require_discrete_gpu = false;

  //---------------------------
};

}
