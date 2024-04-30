#pragma once

#include <Camera/src/Object/Entity.h>
#include <vector>


namespace cam{

struct Structure{
  //---------------------------

  int ID = 0;
  std::vector<cam::Entity*> vec_camera;
  cam::Entity* cam_current = nullptr;

  //---------------------------
};

}
