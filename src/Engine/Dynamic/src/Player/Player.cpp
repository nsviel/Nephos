#include "Player.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace dyn::player{

//Constructor / Destructor
Player::Player(dyn::Node* node_dynamic){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();

  this->dat_selection = node_data->get_dat_selection();
  this->dat_set = node_data->get_dat_set();

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::update(){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  state.locked = set->is_locked;

  this->manage_update(set);

  //---------------------------
}
void Player::reset(){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  this->manage_reset(set);

  //---------------------------
}

//Player function
void Player::button_play(){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  if(!state.play){
    state.play = true;
    state.pause = false;
  }else{
    state.pause = false;
  }

  this->manage_state(set);

  //---------------------------
}
void Player::button_pause(){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  state.pause = !state.pause;

  this->manage_state(set);

  //---------------------------
}
void Player::button_stop(){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  state.play = false;
  state.pause = true;
  timestamp.current = timestamp.begin;

  this->manage_state(set);
  this->manage_restart(set);

  //---------------------------
}
void Player::button_restart(){
  //---------------------------

  state.restart = !state.restart;

  //---------------------------
}
void Player::button_record(){
  //---------------------------

  state.record = !state.record;

  //---------------------------
}
void Player::button_lock(bool value){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  set->is_locked = value;

  //---------------------------
}
void Player::button_close(){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  dat_set->remove_active_entity(set);

  //---------------------------
}

void Player::manage_state(dat::base::Set* set){
  //---------------------------

  //Entity
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity)){
      sensor->state = state;
    }
  }

  //Subset
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->manage_state(subset);
  }

  //---------------------------
}
void Player::manage_update(dat::base::Set* set){
  timestamp = {};
  //---------------------------

  //Entity
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

  //Subset
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
void Player::manage_restart(dat::base::Set* set){
  //---------------------------

  //Entity
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity)){
      sensor->manage_ts_query(timestamp.begin);
    }
  }

  //Subset
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->manage_restart(subset);
  }

  //---------------------------
}
void Player::manage_reset(dat::base::Set* set){
  //---------------------------

  //Entity
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity)){
      sensor->manage_ts_query(timestamp.begin);
    }
  }

  //Subset
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->manage_reset(subset);
  }

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
