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
void Player::update(){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  this->manage_update(set);

  //---------------------------
}

//Player function
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
    //subset->player.player_play();
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
    //subset->player.player_pause();
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
    //subset->player.player_stop();
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
    //subset->player.player_restart();
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
    //subset->player.player_record();
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
    //subset->player.player_lock(value);
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
    //subset->player.player_close();
  }
*/
  //---------------------------
}

void Player::manage_update(dat::base::Set* set){
  timestamp = {};
  //---------------------------

  //Aplly on sensors
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity)){
      if(sensor->timestamp.begin != -1 && sensor->timestamp.end != -1){
        timestamp.begin = (timestamp.begin != -1) ? std::max(timestamp.begin, sensor->timestamp.begin) : sensor->timestamp.begin;
        timestamp.end = (timestamp.end != -1) ? std::min(timestamp.end, sensor->timestamp.end) : sensor->timestamp.end;
        timestamp.current = std::max(timestamp.current, sensor->timestamp.current);
        timestamp.duration = timestamp.end - timestamp.begin;
      }
    }
  }

  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->manage_update(subset);
  }

  //---------------------------
}
void Player::manage_query(float value){
  //---------------------------
/*
  //Aplly on sensors
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity)){
      sensor->manage_ts_query(value);
    }
  }

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    dyn::base::Player* player = &//subset->player;

    float ts_duration = player->ts_end - player->ts_beg;
    float ts_query = value * (ts_duration / 100.0);
    ts_query = ts_query + player->ts_beg;

    //subset->player.manage_query(ts_query);
  }
*/
  //---------------------------
}
void Player::manage_restart(){
  //---------------------------
/*
  if(restart == false){
    this->player_stop();
  }else{
    this->manage_query(ts_beg);
  }
*/
  //---------------------------
}
void Player::manage_reset(){
  //---------------------------
/*
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity)){
      sensor->manage_ts_query(ts_beg);
    }
  }

  //Restart player
  this->manage_query(ts_beg);
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
