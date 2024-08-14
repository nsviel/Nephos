#pragma once

#include <Element/src/Base/Set.h>
#include <vector>

namespace dat::base{class Set;}
namespace utl::base{class Element;}


namespace dat::graph{

struct Structure{
  //---------------------------

  dat::base::Set set_main;
  utl::base::Element* selection = nullptr;

  //---------------------------
};

}
