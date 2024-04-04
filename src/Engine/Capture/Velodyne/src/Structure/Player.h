#pragma once


namespace velodyne::structure{

struct Player{
  //---------------------------

  bool play = true;
  bool pause = false;
  bool restart = true;

  int idx_beg = -1;
  int idx_cur = -1;
  int idx_end = -1;

  //---------------------------
};

}
