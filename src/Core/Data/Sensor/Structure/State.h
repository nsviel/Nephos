#pragma once


namespace dat::sensor{

struct State{
  //---------------------------

  bool play = true;
  bool pause = false;
  bool replay = true;
  bool record = false;
  bool locked = false;
  bool query = false;

  //---------------------------
};

}
