#include "Player.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace dyn::player{

//Constructor / Destructor
Player::Player(dyn::Node* node_dynamic){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();

  this->dat_selection = node_data->get_dat_selection();

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::player_play(){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  if(!state.play){
    state.play = true;
    state.pause = false;
  }else{
    state.pause = false;
  }

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player.player_play();
  }

  //---------------------------
}
void Player::player_pause(){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  state.pause = !state.pause;

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player.player_pause();
  }

  //---------------------------
}
void Player::player_stop(){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  state.play = false;
  state.pause = true;

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player.player_stop();
  }

  //---------------------------
}
void Player::player_restart(){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  state.restart = !state.restart;

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player.player_restart();
  }

  //---------------------------
}
void Player::player_record(){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  state.record = !state.record;

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player.player_record();
  }

  //---------------------------
}
void Player::player_lock(bool value){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  set->is_locked = value;

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player.player_lock(value);
  }

  //---------------------------
}
void Player::player_close(){
  dat::base::Set* set = dat_selection->get_selected_set();
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

}
