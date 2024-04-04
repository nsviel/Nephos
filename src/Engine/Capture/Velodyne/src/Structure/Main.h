#pragma once

#include <Velodyne/src/Structure/Player.h>
#include <Velodyne/src/Structure/Data.h>
#include <Velodyne/src/Structure/Thread.h>
#include <Velodyne/src/Structure/Server.h>


namespace vld::structure{

struct Main{
  //---------------------------

  vld::structure::Data data;
  vld::structure::Player player;
  vld::structure::Thread thread;
  vld::structure::Server server;

  //---------------------------
};

}
