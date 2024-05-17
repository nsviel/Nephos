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
  this->player = new k4n::dev::Player(node_k4n, this);

  //---------------------------
}
Master::~Master(){}

//Main function
void Master::reset(){
  //---------------------------
/*
  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      sensor->manage_reset();
    }
  }

  //Restart player
  this->player_query_ts(ts_beg);
*/
  //---------------------------
}
void Master::info(){
  //---------------------------

  gui_master->show_master_info(this);

  //---------------------------
}

//Master function
void Master::manage_color_control(){
  //---------------------------
/*
  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      k4n_config->make_sensor_color_configuration(sensor);
    }
  }

  //Restart player
  this->player_query_ts(ts_beg);
*/
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
void Master::manage_restart(){
  /*
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      //Set playback to begin
      float& ts_beg = player->get_ts_beg();
      auto ts_querry = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(ts_beg));
      sensor->synchro.seek_timestamp(ts_querry, K4A_PLAYBACK_SEEK_DEVICE_TIME);
      sensor->device.idx_cloud = 0;
    }
  }

  //---------------------------
  player->player_query_ts(player->get_ts_beg());*/
}

}
