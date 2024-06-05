#include "Manager.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace dyn::player{

//Constructor / Destructor
Manager::Manager(dyn::Node* node_dynamic){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();

  this->dat_selection = node_data->get_dat_selection();

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::manage_update(){
  //---------------------------
/*
  //Aplly on sensors
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity)){
      if(sensor->timestamp.begin != -1 && sensor->timestamp.end != -1){
        this->ts_beg = (ts_beg != -1) ? std::max(ts_beg, ts_beg) : sensor->timestamp.begin;
        this->ts_end = (ts_end != -1) ? std::min(ts_end, ts_end) : sensor->timestamp.end;
        this->ts_duration = ts_end - ts_beg;
      }
    }
  }



/*
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    dyn::base::Manager* player = &subset->player;

    float ts_duration = player->ts_end - player->ts_beg;
    float ts_cur = player->ts_cur - player->ts_beg;
    float percentage = ts_cur / ts_duration * 100.0;

    this->ts_cur = percentage;
  }

  //Recursive call
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    subset->player.manage_update();
  }
*/
  //---------------------------
}
void Manager::manage_query(float value){
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
    dyn::base::Manager* player = &subset->player;

    float ts_duration = player->ts_end - player->ts_beg;
    float ts_query = value * (ts_duration / 100.0);
    ts_query = ts_query + player->ts_beg;

    subset->player.manage_query(ts_query);
  }
*/
  //---------------------------
}
void Manager::manage_restart(){
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
void Manager::manage_reset(){
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
void Manager::manage_configuration(){
  //---------------------------


  //---------------------------
}
void Manager::manage_forward(){
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
