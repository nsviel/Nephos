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
void Player::loop(){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  //Update
  state.locked = set->is_locked;
  this->manage_update(set);

  //Check for loop end
  if(timestamp.current >= timestamp.end){
    this->manage_restart(set);
  }

  //---------------------------
}
void Player::reset(){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  this->manage_reset(set);

  //---------------------------
}

//Player function
void Player::button_query(float value){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  this->manage_query(set, value);

  //---------------------------
}
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
void Player::button_forward(float value){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  float ts_forward = timestamp.current + 5 * value;
  if(ts_forward > timestamp.end) ts_forward = timestamp.end;
  if(ts_forward < timestamp.begin) ts_forward = timestamp.begin;

  this->manage_query(set, ts_forward);

  //---------------------------
}

//Subfunction
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
void Player::manage_restart(dat::base::Set* set){
  //---------------------------

  //Entity
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity)){
      sensor->manage_query(timestamp.begin);
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
      sensor->manage_query(timestamp.begin);
    }
  }

  //Subset
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->manage_reset(subset);
  }

  //---------------------------
}
void Player::manage_query(dat::base::Set* set, float value){
  //---------------------------

  //Entity
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity)){
      sensor->manage_query(value);
    }
  }

  //Subset
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->manage_query(subset, value);
  }

  //---------------------------
}

}