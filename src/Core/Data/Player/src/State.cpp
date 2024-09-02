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
  std::shared_ptr<dat::base::Set> set = gph_selection->get_selected_set();
  if(!set) return;
  //---------------------------

  //Update
  ply_struct->state.locked = set->is_locked;
  this->manage_update(*set);

  //Check for loop end
  if(!ply_struct->state.query && ply_struct->timestamp.current >= ply_struct->timestamp.end){
    this->manage_restart(*set);
  }
  ply_struct->state.query = false;

  //---------------------------
}
void State::reset(){
  std::shared_ptr<dat::base::Set> set = gph_selection->get_selected_set();
  if(!set) return;
  //---------------------------

  this->manage_reset(*set);

  //---------------------------
}

//State function
bool State::has_state(dat::base::Set& set){
  //---------------------------

  //Entity
  for(auto& entity : set.list_entity){
    auto sensor = std::dynamic_pointer_cast<dat::base::Sensor>(entity);
    if(sensor){
      return true;
    }
  }

  //Subset
  for(auto& subset : set.list_subset){
    if(has_state(*subset)) return true;
  }

  //---------------------------
  return false;
}
void State::manage_state(dat::base::Set& set){
  //---------------------------

  //Entity
  for(auto& entity : set.list_entity){
    auto sensor = std::dynamic_pointer_cast<dat::base::Sensor>(entity);
    if(sensor){
      sensor->profiler.pause = ply_struct->state.pause;
      sensor->state.pause = ply_struct->state.pause;
      sensor->pause(ply_struct->state.pause);
    }
  }

  //Subset
  for(auto& subset : set.list_subset){
    this->manage_state(*subset);
  }

  //---------------------------
}
void State::manage_update(dat::base::Set& set){
  //---------------------------

  ply_struct->timestamp = {};

  //Entity
  for(auto& entity : set.list_entity){
    auto sensor = std::dynamic_pointer_cast<dat::base::Sensor>(entity);
    if(sensor){
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
  for(auto& subset : set.list_subset){
    this->manage_update(*subset);
  }

  //---------------------------
}
void State::manage_restart(dat::base::Set& set){
  //---------------------------

  //If restart not activated
  if(ply_struct->state.replay == false){
    ply_struct->state.play = false;
    ply_struct->state.pause = true;
    ply_struct->timestamp.current = ply_struct->timestamp.begin;
    this->manage_state(set);
  }

  //Query start entity
  for(auto& entity : set.list_entity){
    auto sensor = std::dynamic_pointer_cast<dat::base::Sensor>(entity);
    if(sensor){
      sensor->query(ply_struct->timestamp.begin);
    }
  }

  //Query start subset
  for(auto& subset : set.list_subset){
    this->manage_restart(*subset);
  }

  //---------------------------
}
void State::manage_reset(dat::base::Set& set){
  //---------------------------

  //Entity
  for(auto& entity : set.list_entity){
    auto sensor = std::dynamic_pointer_cast<dat::base::Sensor>(entity);
    if(sensor){
      sensor->query(ply_struct->timestamp.begin);
    }
  }

  //Subset
  for(auto& subset : set.list_subset){
    this->manage_reset(*subset);
  }

  //---------------------------
}
void State::manage_query(dat::base::Set& set, float value){
  //---------------------------

  //Entity
  for(auto& entity : set.list_entity){
    auto sensor = std::dynamic_pointer_cast<dat::base::Sensor>(entity);
    if(sensor){
      sensor->query(value);
    }
  }

  //Subset
  for(auto& subset : set.list_subset){
    this->manage_query(*subset, value);
  }

  //---------------------------
}

}
