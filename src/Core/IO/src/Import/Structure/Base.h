#pragma once

#include <Element/src/Base/Entity.h>
#include <Element/src/Base/Set.h>
#include <string>

namespace dat::base{class Object;}


namespace io::importer{

struct Base{
  //---------------------------

  virtual utl::base::Element* import(utl::base::Path path){return nullptr;}

  std::string format = "";
  bool require_discrete_gpu = false;

  //---------------------------
};

}
