#pragma once

#include <Dynamic/src/Player/Structure.h>
#include <Utility/Specific/Common.h>


namespace k4n::structure{

struct Player : public dyn::player::Structure{
  //---------------------------
string name = "hello";
  void player_update(){

  }
  void player_play(){
    if(!play){
      play = true;
      pause = false;
    }else{
      pause = false;
    }
  }
  void player_pause(bool value){
    pause = value;
  }
  void player_query_ts(float value){}
  void player_stop(){}
  void player_restart(){
      restart = !restart;
  }
  void player_record(){
      record = !record;
  }
  void player_close(){}
  void player_lock(){}

  //---------------------------
};

}
