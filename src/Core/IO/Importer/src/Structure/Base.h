#pragma once

#include <Data/Base/Element/Entity.h>
#include <Data/Base/Element/Set.h>
#include <string>

namespace dat::base{class Object;}


namespace io::imp{

struct Base{
  //---------------------------

  virtual std::shared_ptr<utl::base::Element> import(utl::base::Path path){return nullptr;}

  std::string format = "";
  bool require_discrete_gpu = false;

  //---------------------------
};

}
