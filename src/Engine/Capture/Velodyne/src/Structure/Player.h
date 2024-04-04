#pragma once


namespace velodyne::structure{

struct Player{
  //---------------------------

  bool play = true;
  bool pause = false;
  bool restart = true;

  int idx_beg = 0;
  int idx_cur = 0;
  int idx_end = 100;

  //---------------------------
};

}
