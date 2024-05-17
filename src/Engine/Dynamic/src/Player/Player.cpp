#include "Player.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace dyn::base{

//Constructor / Destructor
Player::Player(dat::base::Set* set){
  //---------------------------

  this->set = set;

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
    subset->player->player_play();
  }

  //---------------------------
}
void Player::player_pause(){
  //---------------------------

  pause = !pause;

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player->player_pause();
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
    subset->player->player_stop();
  }

  //---------------------------
}
void Player::player_restart(){
  //---------------------------

  restart = !restart;

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player->player_restart();
  }

  //---------------------------
}
void Player::player_record(){
  //---------------------------

  record = !record;

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player->player_record();
  }

  //---------------------------
}
void Player::player_lock(){
  //---------------------------

  set->is_locked = !set->is_locked;

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player->player_record();
  }

  //---------------------------
}
void Player::player_info(){
  //---------------------------

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player->player_info();
  }

  //---------------------------
}
void Player::player_update(){
  //---------------------------

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player->player_update();
  }

  //---------------------------
}
void Player::player_close(){
  //---------------------------

  set->is_locked = !set->is_locked;

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player->player_record();
  }

  //---------------------------
}
void Player::player_query_ts(float value){
  //---------------------------

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player->player_query_ts(value);
  }

  //---------------------------
}

}
