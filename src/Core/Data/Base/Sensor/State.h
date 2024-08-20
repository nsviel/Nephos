#pragma once


namespace dyn::prc::base{

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
