#include "State.h"

#include <Data/Player/Namespace.h>
#include <Data/Graph/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Data/Base/Namespace.h>


namespace dat::ply{

//Constructor / Destructor
State::State(dat::ply::Node* node_player){
  //---------------------------

  dat::gph::Node* node_graph = node_player->get_node_graph();

  this->gph_selection = node_graph->get_gph_selection();

  //---------------------------
}
State::~State(){}

//Main function
void State::loop(){
  dat::base::Set* set = gph_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  //Update
  state.locked = set->is_locked;
  this->manage_update(set);

  //Check for loop end
  if(!state.query && timestamp.current >= timestamp.end){
    this->manage_restart(set);
  }
  state.query = false;

  //---------------------------
}
void State::reset(){
  dat::base::Set* set = gph_selection->get_selected_set();
  //---------------------------

  this->manage_reset(set);

  //---------------------------
}

//State function
void State::manage_state(dat::base::Set* set){
/*  if(set == nullptr) return;
  //---------------------------

  //Entity
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(entity)){
      sensor->state = state;
      sensor->set_pause(state.pause);
    }
  }

  //Subset
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->manage_state(subset);
  }
*/
  //---------------------------
}
void State::manage_update(dat::base::Set* set){
  if(set == nullptr) return;
  //---------------------------
/*
  timestamp = {};

  //Entity
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(entity)){
      if(sensor->timestamp.begin != -1 && sensor->timestamp.end != -1){
        timestamp.begin = (timestamp.begin != -1) ? std::max(timestamp.begin, sensor->timestamp.begin) : sensor->timestamp.begin;
        timestamp.end = (timestamp.end != -1) ? std::min(timestamp.end, sensor->timestamp.end) : sensor->timestamp.end;
        timestamp.current = std::max(timestamp.current, sensor->timestamp.current);
        timestamp.duration = timestamp.end - timestamp.begin;
      }
    }
  }

  //Truncate values for avoid overvalues
  timestamp.begin = math::ceil(timestamp.begin, 2);
  timestamp.end = math::truncate(timestamp.end, 2);

  //Subset
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->manage_update(subset);
  }
*/
  //---------------------------
}
void State::manage_restart(dat::base::Set* set){
  if(set == nullptr) return;
  //---------------------------
/*
  if(!state.replay){
    state.play = false;
    state.pause = true;
    timestamp.current = timestamp.begin;
    this->manage_state(set);
  }

  //Entity
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(entity)){
      sensor->manage_query(timestamp.begin);
    }
  }

  //Subset
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->manage_restart(subset);
  }
*/
  //---------------------------
}
void State::manage_reset(dat::base::Set* set){
  //---------------------------
/*
  //Entity
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(entity)){
      sensor->manage_query(timestamp.begin);
    }
  }

  //Subset
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->manage_reset(subset);
  }
*/
  //---------------------------
}
void State::manage_query(dat::base::Set* set, float value){
  //---------------------------
/*
  //Entity
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(entity)){
      sensor->manage_query(value);
    }
  }

  //Subset
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->manage_query(subset, value);
  }
*/
  //---------------------------
}

}
