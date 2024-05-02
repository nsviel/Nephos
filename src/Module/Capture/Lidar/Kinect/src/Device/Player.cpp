#include "Player.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace k4n::dev{

//Constructor / Destructor
Player::Player(dat::base::Set* set) : dyn::Player(set){
  //---------------------------


  //---------------------------
}
Player::~Player(){}

//Main function
void Player::player_update(){
  //---------------------------

  //---------------------------
}
void Player::player_play(){
  //---------------------------

  if(!play){
    play = true;
    pause = false;
  }else{
    pause = false;
  }

  //---------------------------
}
void Player::player_pause(){
  //---------------------------

  pause = !pause;

  //---------------------------
}
void Player::player_query_ts(float value){
  //---------------------------

  //---------------------------
}
void Player::player_stop(){
  //---------------------------

  //---------------------------
}
void Player::player_restart(){
  //---------------------------

  restart = !restart;

  //---------------------------
}
void Player::player_record(){
  //---------------------------

  record = !record;

  //---------------------------
}
void Player::player_close(){
  //---------------------------

  //---------------------------
}
void Player::player_lock(){
  //---------------------------

  //---------------------------
}

}
