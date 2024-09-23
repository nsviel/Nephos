#pragma once

#include <Camera/src/Structure/Path.h>
#include <Camera/src/Object/Entity.h>
#include <memory>
#include <vector>


namespace cam{

struct Structure{
  //---------------------------

  int ID = 0;
  std::vector< std::shared_ptr<cam::Entity> > vec_camera;
  std::vector<cam::mode::Base*> vec_mode;
  std::shared_ptr<cam::Entity> cam_current;
  cam::structure::Path path;
  cam::mode::Base* active_mode;

  //---------------------------
};

}
