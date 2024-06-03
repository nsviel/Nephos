#include "Player.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace dyn::base{

//Constructor / Destructor
Player::Player(dat::base::Set* set){
  //---------------------------

  this->set = set;
  this->ts_beg = 0;
  this->ts_end = 100;

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::player_play(){
  //---------------------------

  if(!play){
    play = true;
    pause = false;
  }else{
    pause = false;
  }

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player.player_play();
  }

  //---------------------------
}
void Player::player_pause(){
  //---------------------------

  pause = !pause;

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player.player_pause();
  }

  //---------------------------
}
void Player::player_stop(){
  //---------------------------

  this->play = false;
  this->pause = true;

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player.player_stop();
  }

  //---------------------------
}
void Player::player_restart(){
  //---------------------------

  restart = !restart;

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player.player_restart();
  }

  //---------------------------
}
void Player::player_record(){
  //---------------------------

  record = !record;

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player.player_record();
  }

  //---------------------------
}
void Player::player_lock(bool value){
  //---------------------------

  set->is_locked = value;

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player.player_lock(value);
  }

  //---------------------------
}
void Player::player_update(){
  //---------------------------

  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    dyn::base::Player* player = &subset->player;

    float ts_duration = player->ts_end - player->ts_beg;
    float ts_cur = player->ts_cur - player->ts_beg;
    float percentage = ts_cur / ts_duration * 100.0;

    this->ts_cur = percentage;
  }

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player.player_update();
  }

  //---------------------------
}
void Player::player_close(){
  //---------------------------
/*
  set->is_locked = !set->is_locked;

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player.player_close();
  }
*/
  //---------------------------
}
void Player::player_query(float value){
  //---------------------------

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    dyn::base::Player* player = &subset->player;

    float ts_duration = player->ts_end - player->ts_beg;
    float ts_query = value * (ts_duration / 100.0);
    ts_query = ts_query + player->ts_beg;

    subset->player.player_query(ts_query);
  }

  //---------------------------
}

//Subfunction
void Player::manage_restart(){
  //---------------------------

  if(restart == false){
    this->player_stop();
  }else{
    this->player_query(ts_beg);
  }

  //---------------------------
}
void Player::manage_reset(){
  //---------------------------
  /*
    for(int i=0; i<list_entity.size(); i++){
      dat::base::Entity* entity = *next(list_entity.begin(), i);

      if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
        sensor->manage_ts_query(player->ts_beg);
      }
    }

    //Restart player
    player.player_query(ts_beg);
  */

  //---------------------------
}
void Player::manage_configuration(){
  //---------------------------


  //---------------------------
}
void Player::manage_forward(){
  //---------------------------
/*
  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::playback::Sensor* sensor = dynamic_cast<k4n::playback::Sensor*>(entity)){
      float ts_forward = ts_cur + 5 * ts_for;
      if(ts_forward > ts_end) ts_forward = ts_end;
      if(ts_forward < ts_beg) ts_forward = ts_beg;

      sensor->manage_ts_query(ts_forward);
    }
  }
*/
  //---------------------------
}

}
