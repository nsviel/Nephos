#include "Master.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::dev{

//Constructor / Destructor
Master::Master(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();

  this->dat_set = node_data->get_set();
  this->k4n_config = new k4n::config::Configuration();

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

  if(mode == k4n::dev::PLAYBACK){
    this->manage_restart();
  }
  else if(mode == k4n::dev::CAPTURE){
    this->manage_restart_thread();
  }

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

  //---------------------------
  player.ts_cur = player.ts_beg;
}
void Master::manage_restart_thread(){
  if(mode == k4n::dev::PLAYBACK) return;
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      sensor->reset_entity();
      sensor->run_thread_capture();
    }
  }

  //---------------------------
  player.ts_cur = player.ts_beg;
}
void Master::manage_restart(){
  if(mode == k4n::dev::CAPTURE) return;
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      //Set playback to begin
      auto ts_querry = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(player.ts_beg));
      sensor->param.playback.seek_timestamp(ts_querry, K4A_PLAYBACK_SEEK_DEVICE_TIME);
      sensor->param.index_cloud = 0;
    }
  }

  //---------------------------
  player.ts_cur = player.ts_beg;
}
void Master::manage_forward(){
  if(mode == k4n::dev::CAPTURE) return;
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      float ts_forward = player.ts_cur + 5 * player.ts_forward;
      if(ts_forward > player.ts_end) ts_forward = player.ts_end;
      if(ts_forward < player.ts_beg) ts_forward = player.ts_beg;

      auto ts_querry = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(ts_forward));
      sensor->param.playback.seek_timestamp(ts_querry, K4A_PLAYBACK_SEEK_DEVICE_TIME);
    }
  }

  //---------------------------
}
void Master::manage_resynchronization(){
  //if(list_entity.size() == 0) player.ts_cur = 0;sayHello();
  //if(list_entity.size() < 2) return;sayHello();
  //if(mode == k4n::dev::CAPTURE) return;sayHello();
  //---------------------------
  //Should be set into another dedicated thread
/*
  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      auto ts_querry = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(player.ts_cur));
      sensor->param.playback.seek_timestamp(ts_querry, K4A_PLAYBACK_SEEK_DEVICE_TIME);
    }
  }*/

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
      k4n::utils::Operation k4n_operation;
      float ts_beg = k4n_operation.find_mkv_ts_beg(sensor->param.path.data);
      float ts_end = k4n_operation.find_mkv_ts_end(sensor->param.path.data);

      this->player.ts_beg = (player.ts_beg != -1) ? std::max(player.ts_beg, ts_beg) : ts_beg;
      this->player.ts_end = (player.ts_end != -1) ? std::min(player.ts_end, ts_end) : ts_end;
      this->player.duration = player.ts_end - player.ts_beg;
      /*}else{
        this->player.ts_beg = 0;
        this->player.ts_end = 0;
        this->player.duration = 0;
      }*/
    }
  }

  //Apply min max timestamp to all sensors
  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      sensor->run_thread_playback(sensor->param.path.data);
    }
  }

  //---------------------------
}
void Master::player_pause(bool value){
  //---------------------------

  this->player.pause = value;

  //---------------------------
}
void Master::player_query_ts(float value){
  if(mode == k4n::dev::CAPTURE) return;
  //---------------------------

  this->player.ts_seek = value;
  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      auto ts_querry = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(value));
      sensor->param.playback.seek_timestamp(ts_querry, K4A_PLAYBACK_SEEK_DEVICE_TIME);
    }
  }

  //---------------------------
}
void Master::player_play(){
  //---------------------------

  if(!player.play){
    player.play = true;
    player.pause = false;
  }else{
    player.pause = false;
  }

  //---------------------------
}
void Master::player_stop(){
  //---------------------------

  //Pause playback thread
  player.play = false;
  player.pause = true;

  //Wait for pause
  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      sensor->wait_threads();
    }
  }

  this->manage_restart();

  //---------------------------
}
void Master::player_restart(){
  //---------------------------

  player.restart = !player.restart;

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
          sensor->stop_threads();
        }
      }
      break;
    }
  }

  //---------------------------
}
void Master::player_record(){
  //---------------------------

  player.record = !player.record;

  //---------------------------
}

//Subfunction
void Master::visibility_normal(){
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    dat::base::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      dat::base::Object* object = sensor->get_object();
      dat::base::Glyph* normal = object->get_glyph(dat::object::glyph::NORMAL);
      normal->set_visibility(operation.normal_visible);
    }
  }

  //---------------------------
}

}
