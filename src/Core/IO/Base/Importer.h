#pragma once

#include <IO/Base/Reference.h>
#include <Utility/Namespace.h>

namespace dat::base{class Object;}


namespace io::base{

struct Importer{
  //---------------------------

  virtual std::shared_ptr<utl::base::Element> import(utl::base::Path path){return nullptr;}
  virtual std::shared_ptr<utl::base::Element> capture(utl::base::Path path){return nullptr;}

  io::base::Reference reference;

  //---------------------------
};

}
