#pragma once

#include <Data/Base/Element/Set.h>
#include <vector>

namespace dat::base{class Set;}
namespace utl::base{class Element;}


namespace dat::elm{

struct Structure{
  //---------------------------

  dat::base::Set set_main;
  std::shared_ptr<utl::base::Element> selection = nullptr;

  //---------------------------
};

}
