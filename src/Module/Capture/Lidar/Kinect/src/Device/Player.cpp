#include "Player.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <Kinect/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace k4n::dev{

//Constructor / Destructor
Player::Player(k4n::dev::Master* master){// : dyn::base::Player(master){
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

  //Pause playback thread
  this->play = false;
  this->pause = true;
/*
  //Wait for pause
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      sensor->wait_threads();
    }
  }
*/
  this->manage_restart();

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

void Player::gui_info(){
  //---------------------------

  //---------------------------
}

//Subfunction
void Player::manage_restart(){
  /*if(mode == k4n::dev::CAPTURE) return;
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      //Set playback to begin
      float& ts_beg = player->get_ts_beg();
      auto ts_querry = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(ts_beg));
      sensor->playback.handle.seek_timestamp(ts_querry, K4A_PLAYBACK_SEEK_DEVICE_TIME);
      sensor->param.index_cloud = 0;
    }
  }

  //---------------------------
  player->player_query_ts(player->get_ts_beg());*/
}

}
