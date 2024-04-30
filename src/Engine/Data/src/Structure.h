#pragma once

#include <Data/src/Base/Set.h>
#include <vector>

namespace dat::base{class Set;}
namespace utl::type{class Element;}


namespace dat{

struct Structure{
  //---------------------------

  dat::base::Set set_main;
  utl::type::Element* selection = nullptr;
  int UID = 0;

  //---------------------------
};

}
