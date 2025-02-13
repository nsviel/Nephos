#pragma once

#include <Velodyne/src/Structure/Player.h>
#include <Velodyne/src/Structure/Data.h>
#include <Velodyne/src/Structure/Server.h>


namespace vld{

struct Structure{
  //---------------------------

  vld::structure::Data data;
  vld::structure::Player player;
  vld::structure::Server server;

  //---------------------------
};

}
