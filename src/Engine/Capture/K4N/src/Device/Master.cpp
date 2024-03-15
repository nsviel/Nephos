#include "Master.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>
#include <Scene/Namespace.h>


namespace k4n::dev{

//Constructor / Destructor
Master::Master(){
  //---------------------------

  this->sce_set = new eng::scene::Set();
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
void Master::insert_sensor(k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  if(sensor->profiler == nullptr){
    cout<<"[error] sensor must be initialized before added to master"<<endl;
    return;
  }
  //---------------------------

  sce_set->insert_entity(this, sensor);

  //---------------------------
}
void Master::reset(){
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
    utl::type::Entity* entity = *next(list_entity.begin(), i);

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
    utl::type::Entity* entity = *next(list_entity.begin(), i);

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
    utl::type::Entity* entity = *next(list_entity.begin(), i);

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
    utl::type::Entity* entity = *next(list_entity.begin(), i);

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
  if(list_entity.size() == 0) player.ts_cur = 0;
  if(list_entity.size() < 2) return;
  if(mode == k4n::dev::CAPTURE) return;
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      auto ts_querry = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(player.ts_cur));
      sensor->param.playback.seek_timestamp(ts_querry, K4A_PLAYBACK_SEEK_DEVICE_TIME);
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
    utl::type::Entity* entity = *next(list_entity.begin(), i);

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
    utl::type::Entity* entity = *next(list_entity.begin(), i);

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
    utl::type::Entity* entity = *next(list_entity.begin(), i);

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
    utl::type::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      sensor->wait_pause();
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
void Master::player_record(){
  //---------------------------

  player.record = !player.record;

  //---------------------------
}

//Subfunction
void Master::visibility_normal(){
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      utl::entity::Object* object = sensor->get_object();
      utl::entity::Glyph* normal = object->get_glyph(utl::entity::object::NORMAL);
      normal->set_visibility(operation.normal_visible);
    }
  }

  //---------------------------
}

}
