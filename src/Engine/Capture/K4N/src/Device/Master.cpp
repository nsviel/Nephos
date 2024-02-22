#include "Master.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>


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
void Master::insert_sensor(k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  if(sensor->profiler == nullptr){
    cout<<"[error] sensor must be initialized before added to master"<<endl;
    return;
  }
  //---------------------------

  this->insert_entity(sensor);
  this->player_update();

  //---------------------------
}
void Master::reset(){
  //---------------------------

  this->manage_restart();

  //---------------------------
}

//Master function
void Master::manage_restart(){
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      auto ts_querry = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(player.ts_beg));
      sensor->param.playback->seek_timestamp(ts_querry, K4A_PLAYBACK_SEEK_DEVICE_TIME);
    }
  }

  //---------------------------
  player.ts_cur = player.ts_beg;
}
void Master::manage_forward(){
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      float ts_forward = player.ts_cur + 5 * player.ts_forward;
      if(ts_forward > player.ts_end) ts_forward = player.ts_end;
      if(ts_forward < player.ts_beg) ts_forward = player.ts_beg;

      auto ts_querry = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(ts_forward));
      sensor->param.playback->seek_timestamp(ts_querry, K4A_PLAYBACK_SEEK_DEVICE_TIME);
    }
  }

  //---------------------------
}
void Master::manage_suppression(k4n::dev::Sensor* sensor){
  //---------------------------

  if(is_locked){
    this->delete_entity_all();
  }else{
    this->delete_entity(sensor);
  }

  //---------------------------
}

//Player function
void Master::player_update(){
  //---------------------------

  //Search for min max timestamp
  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      if(sensor->param.is_playback){
        k4n::utils::Operation k4n_operation;
        float ts_beg = k4n_operation.find_mkv_ts_beg(sensor->param.path_data);
        float ts_end = k4n_operation.find_mkv_ts_end(sensor->param.path_data);

        this->player.ts_beg = (player.ts_beg != -1) ? std::max(player.ts_beg, ts_beg) : ts_beg;
        this->player.ts_end = (player.ts_end != -1) ? std::min(player.ts_end, ts_end) : ts_end;
        this->player.duration = player.ts_end - player.ts_beg;
      }else{
        this->player.ts_beg = 0;
        this->player.ts_end = 0;
        this->player.duration = 0;
      }

    }
  }

  //Apply min max timestamp to all sensors
  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      sensor->run_playback(sensor->param.path_data);
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
  //---------------------------

  this->player.ts_seek = value;
  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      auto ts_querry = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(value));
      sensor->param.playback->seek_timestamp(ts_querry, K4A_PLAYBACK_SEEK_DEVICE_TIME);
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

  //Restart playbacks
  player.play = true;
  player.pause = false;
  this->manage_restart();

  //Set play state
  player.play = false;
  player.pause = true;

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
