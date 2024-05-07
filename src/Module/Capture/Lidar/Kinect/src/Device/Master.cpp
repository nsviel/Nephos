#include "Master.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::dev{

//Constructor / Destructor
Master::Master(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();

  this->dat_set = node_data->get_data_set();
  this->k4n_config = new k4n::utils::Configuration();
  this->gui_master = new k4n::gui::Master(node_k4n);

  //this->engine = engine;
  this->type = "k4n::device::Master";
  this->icon = ICON_FA_USER;
  this->is_locked = true;
  this->is_suppressible = true;

  //---------------------------
}
Master::~Master(){}

//Main function
void Master::reset_set(){
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      sensor->manage_reset();
    }
  }

  //Restart player
  this->player_query_ts(ts_beg);

  //---------------------------
}
void Master::info(){
  //---------------------------

  gui_master->show_master_info(this);

  //---------------------------
}

//Master function
void Master::manage_color_control(){
  if(mode == k4n::dev::PLAYBACK) return;
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      k4n_config->make_sensor_color_configuration(sensor);
    }
  }

  //Restart player
  this->player_query_ts(ts_beg);

  //---------------------------
}
void Master::manage_forward(){
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
void Master::manage_configuration(){
  if(mode == k4n::dev::PLAYBACK) return;
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      sensor->color.config = config.color;
      sensor->depth.config = config.depth;
      sensor->ir.config = config.ir;
    }
  }

  //---------------------------
}

//Player function
void Master::player_update(){
  if(mode == k4n::dev::CAPTURE) return;
  //---------------------------

  //Search for min max timestamp
  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      float mkv_ts_beg = k4n_importer->find_mkv_ts_beg(sensor->param.path.data);
      float mkv_ts_end = k4n_importer->find_mkv_ts_end(sensor->param.path.data);

      ts_beg = (ts_beg != -1) ? std::max(ts_beg, mkv_ts_beg) : mkv_ts_beg;
      ts_end = (ts_end != -1) ? std::min(ts_end, mkv_ts_end) : mkv_ts_end;
      this->set_duration(ts_end - ts_beg);
      /*}else{
        this->player->ts_beg = 0;
        this->player->ts_end = 0;
        this->player->duration = 0;
      }*/
    }
  }

  //Apply min max timestamp to all sensors
  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      sensor->run_thread();
    }
  }

  //set_parent->player_update(player);

  //---------------------------
}
void Master::player_query_ts(float value){
  if(mode == k4n::dev::CAPTURE) return;
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::playback::Sensor* sensor = dynamic_cast<k4n::playback::Sensor*>(entity)){
      sensor->manage_ts_query(value);
    }
  }

  //---------------------------
}
void Master::player_close(){
  //---------------------------

  switch(mode){
    //If playback, close selected one
    case k4n::dev::PLAYBACK:{
      dat_set->remove_entity(this, active_entity);
      break;
    }
    //If capture, stop all sensor threads
    case k4n::dev::CAPTURE:{
      for(int i=0; i<list_entity.size(); i++){
        dat::base::Entity* entity = *next(list_entity.begin(), i);

        if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
          sensor->stop_thread();
        }
      }
      break;
    }
  }

  //---------------------------
}

}
