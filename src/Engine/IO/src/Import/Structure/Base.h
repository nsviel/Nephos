#pragma once

#include <Data/src/Base/Entity.h>
#include <Data/src/Base/Set.h>
#include <string>

namespace dat::base{class Object;}


namespace ldr::importer{

struct Base{
  //---------------------------

  virtual utl::base::Element* import(utl::base::Path path){return nullptr;}

  std::string format = "";
  bool require_discrete_gpu = false;

  //---------------------------
};

}
