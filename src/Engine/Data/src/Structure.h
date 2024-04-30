#pragma once

#include <vector>

namespace dat::base{class Set;}
namespace cam{class Entity;}


namespace dat{

struct Structure{
  //---------------------------

  std::vector<cam::Entity*> vec_camera;
  dat::base::Set* set_main;

  //---------------------------
};

}
