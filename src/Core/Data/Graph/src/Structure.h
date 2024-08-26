#pragma once

#include <Data/Base/Element/Set.h>
#include <Utility/Namespace.h>

namespace dat::base{class Set;}
namespace utl::base{class Element;}


namespace dat::gph{

struct Structure{
  //---------------------------

  std::shared_ptr<dat::base::Set> set_main;
  std::weak_ptr<utl::base::Element> selection;

  //---------------------------
};

}
