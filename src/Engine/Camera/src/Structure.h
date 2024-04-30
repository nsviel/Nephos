#pragma once

#include <Camera/src/Object/Entity.h>
#include <vector>


namespace cam{

struct Structure{
  //---------------------------

  std::vector<cam::Entity*> vec_camera;
  cam::Entity* cam_current;

  //---------------------------
};

}
