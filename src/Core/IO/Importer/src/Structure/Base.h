#pragma once

#include <Base/Element/Entity.h>
#include <Base/Element/Set.h>
#include <string>

namespace dat::base{class Object;}


namespace io::imp{

struct Base{
  //---------------------------

  virtual utl::base::Element* import(utl::base::Path path){return nullptr;}

  std::string format = "";
  bool require_discrete_gpu = false;

  //---------------------------
};

}
