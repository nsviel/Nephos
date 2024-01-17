#include "Master.h"

#include <Engine/Engine.h>
#include <Engine/Capture/K4N/Utils/Namespace.h>

namespace k4n::dev{


//Constructor / Destructor
Master::Master(){//Engine* engine){
  //---------------------------

  //this->engine = engine;
  this->device_type = "k4n::device::Master";
  this->icon = ICON_FA_TRAIN;


  //---------------------------
}
Master::~Master(){}

//Main function
void Master::add_sensor(k4n::dev::Sensor* sensor){
  //---------------------------

  k4n::utils::Operation k4n_operation;
  k4n_operation.playback_find_duration(sensor);
  this->player.ts_beg = (player.ts_beg != -1) ? std::max(player.ts_beg, sensor->player.ts_beg) : sensor->player.ts_beg;
  this->player.ts_end = (player.ts_end != -1) ? std::min(player.ts_end, sensor->player.ts_end) : sensor->player.ts_end;
  this->player.duration = player.ts_end - player.ts_beg;

  this->list_sensor.push_back(sensor);
  this->list_entity.push_back(sensor);

  //---------------------------
}

//Player function
void Master::set_pause(bool value){
  //---------------------------

  this->player.pause = value;
  for(int i=0; i<list_sensor.size(); i++){
    k4n::dev::Sensor* sensor = *next(list_sensor.begin(), i);
    sensor->set_pause(value);
  }

  //---------------------------
}
void Master::set_desired_timestamp(float value){
  //---------------------------

  this->player.ts_seek = value;
  for(int i=0; i<list_sensor.size(); i++){
    k4n::dev::Sensor* sensor = *next(list_sensor.begin(), i);
    sensor->set_desired_timestamp(value);
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



}
