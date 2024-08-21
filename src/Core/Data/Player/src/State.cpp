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

  this->ply_struct = node_player->get_ply_struct();
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
  ply_struct->state.locked = set->is_locked;
  this->manage_update(set);

  //Check for loop end
  if(!ply_struct->state.query && ply_struct->timestamp.current >= ply_struct->timestamp.end){
    this->manage_restart(set);
  }
  ply_struct->state.query = false;

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
  if(set == nullptr) return;
  //---------------------------

  //Entity
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(entity)){
      sensor->state = ply_struct->state;
      sensor->set_pause(ply_struct->state.pause);
    }
  }

  //Subset
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->manage_state(subset);
  }

  //---------------------------
}
void State::manage_update(dat::base::Set* set){
  if(set == nullptr) return;
  //---------------------------

  ply_struct->timestamp = {};

  //Entity
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(entity)){
      if(sensor->timestamp.begin != -1 && sensor->timestamp.end != -1){
        ply_struct->timestamp.begin = (ply_struct->timestamp.begin != -1) ? std::max(ply_struct->timestamp.begin, sensor->timestamp.begin) : sensor->timestamp.begin;
        ply_struct->timestamp.end = (ply_struct->timestamp.end != -1) ? std::min(ply_struct->timestamp.end, sensor->timestamp.end) : sensor->timestamp.end;
        ply_struct->timestamp.current = std::max(ply_struct->timestamp.current, sensor->timestamp.current);
        ply_struct->timestamp.duration = ply_struct->timestamp.end - ply_struct->timestamp.begin;
      }
    }
  }

  //Truncate values for avoid overvalues
  ply_struct->timestamp.begin = math::ceil(ply_struct->timestamp.begin, 2);
  ply_struct->timestamp.end = math::truncate(ply_struct->timestamp.end, 2);

  //Subset
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->manage_update(subset);
  }

  //---------------------------
}
void State::manage_restart(dat::base::Set* set){
  if(set == nullptr) return;
  //---------------------------

  //If restart not activated
  if(ply_struct->state.replay == false){
    ply_struct->state.play = false;
    ply_struct->state.pause = true;
    ply_struct->timestamp.current = ply_struct->timestamp.begin;
    this->manage_state(set);
  }

  //Query start entity
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(entity)){
      sensor->manage_query(ply_struct->timestamp.begin);
    }
  }

  //Query start subset
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->manage_restart(subset);
  }

  //---------------------------
}
void State::manage_reset(dat::base::Set* set){
  //---------------------------

  //Entity
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(entity)){
      sensor->manage_query(ply_struct->timestamp.begin);
    }
  }

  //Subset
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->manage_reset(subset);
  }

  //---------------------------
}
void State::manage_query(dat::base::Set* set, float value){
  //---------------------------

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

  //---------------------------
}

}
