#include "Master.h"

#include <Engine/Capture/K4N/Utils/Namespace.h>

namespace k4n::dev{


//Constructor / Destructor
Master::Master(){
  //---------------------------

  //this->engine = engine;
  this->type = "k4n::device::Master";
  this->icon = ICON_FA_USER;
  this->is_locked = true;
  this->is_suppressible = true;

  //---------------------------
}
Master::~Master(){}

//Main function
void Master::insert_sensor_playback(k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  //---------------------------

  this->insert_entity(sensor);
  this->list_sensor.push_back(sensor);
  this->update_player();

  //---------------------------
}
void Master::insert_sensor_capture(k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  //---------------------------

  this->list_entity.push_back(sensor);
  this->list_sensor.push_back(sensor);
  this->selected_entity = sensor;
  this->nb_entity++;

  //---------------------------
}

//Player function
void Master::update_player(){
  //---------------------------

  //Search for min max timestamp
  for(int i=0; i<list_sensor.size(); i++){
    k4n::dev::Sensor* sensor = *next(list_sensor.begin(), i);

    k4n::utils::Operation k4n_operation;
    float ts_beg = k4n_operation.find_mkv_ts_beg(sensor->param.file_path);
    float ts_end = k4n_operation.find_mkv_ts_end(sensor->param.file_path);

    this->player.ts_beg = (player.ts_beg != -1) ? std::max(player.ts_beg, ts_beg) : ts_beg;
    this->player.ts_end = (player.ts_end != -1) ? std::min(player.ts_end, ts_end) : ts_end;
    this->player.duration = player.ts_end - player.ts_beg;
  }

  //Apply min max timestamp to all sensors
  for(int i=0; i<list_sensor.size(); i++){
    k4n::dev::Sensor* sensor = *next(list_sensor.begin(), i);
    sensor->player = player;
    sensor->run_playback(sensor->param.file_path);
  }

  //---------------------------
}
void Master::set_pause(bool value){
  //---------------------------

  this->player.pause = value;
  for(int i=0; i<list_sensor.size(); i++){
    k4n::dev::Sensor* sensor = *next(list_sensor.begin(), i);
    sensor->player.pause = value;
  }

  //---------------------------
}
void Master::set_desired_timestamp(float value){
  //---------------------------

  this->player.ts_seek = value;
  for(int i=0; i<list_sensor.size(); i++){
    k4n::dev::Sensor* sensor = *next(list_sensor.begin(), i);
    sensor->player.ts_seek = value;
  }

  //---------------------------
}
void Master::set_play(){
  //---------------------------

  if(!player.play){
    player.play = true;
    player.pause = false;
  }else{
    player.pause = false;
  }

  for(int i=0; i<list_sensor.size(); i++){
    k4n::dev::Sensor* sensor = *next(list_sensor.begin(), i);
    sensor->player.play = player.play;
    sensor->player.pause = player.pause;
  }

  //---------------------------
}
void Master::set_stop(){
  //---------------------------

  player.ts_seek = player.ts_beg;
  player.play = false;
  player.pause = true;

  for(int i=0; i<list_sensor.size(); i++){
    k4n::dev::Sensor* sensor = *next(list_sensor.begin(), i);
    sensor->player.play = player.play;
    sensor->player.pause = player.pause;
    sensor->player.ts_seek = player.ts_seek;
  }

  //---------------------------
}
void Master::set_restart(){
  //---------------------------

  player.restart = !player.restart;

  for(int i=0; i<list_sensor.size(); i++){
    k4n::dev::Sensor* sensor = *next(list_sensor.begin(), i);
    sensor->player.restart = player.restart;
  }

  //---------------------------
}
void Master::set_record(){
  //---------------------------

  player.record = !player.record;

  for(int i=0; i<list_sensor.size(); i++){
    k4n::dev::Sensor* sensor = *next(list_sensor.begin(), i);
    sensor->player.record = player.record;
  }

  //---------------------------
}
void Master::manage_restart(){
  //---------------------------

  for(int i=0; i<list_sensor.size(); i++){
    k4n::dev::Sensor* sensor = *next(list_sensor.begin(), i);

    sensor->player.play = player.restart;
    sensor->player.pause = !player.restart;
    sensor->player.ts_seek = player.ts_beg;
  }

  //---------------------------
}



}
