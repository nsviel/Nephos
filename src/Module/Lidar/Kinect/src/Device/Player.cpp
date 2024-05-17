#include "Player.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n::dev{

//Constructor / Destructor
Player::Player(k4n::dev::Master* master) : dyn::base::Player(master){
  //---------------------------


  //---------------------------
}
Player::~Player(){}

//Main function
void Player::player_stop(){
  //---------------------------

  //Pause playback thread
  this->play = false;
  this->pause = true;
/*
  //Wait for pause
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      sensor->wait_threads();
    }
  }

  this->manage_restart();
*/
  //---------------------------
}
void Player::player_update(){
  //---------------------------

  //Search for min max timestamp
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
/*      float mkv_ts_beg = k4n_importer->find_mkv_ts_beg(sensor->path.data);
      float mkv_ts_end = k4n_importer->find_mkv_ts_end(sensor->path.data);

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
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      //sensor->run_thread();
    }
  }

  //set_parent->player_update();

  //---------------------------
}
void Player::player_query_ts(float value){
  //---------------------------

  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(k4n::playback::Sensor* sensor = dynamic_cast<k4n::playback::Sensor*>(entity)){
      sensor->manage_ts_query(value);
    }
  }

  //---------------------------
}
void Player::player_close(){
  //---------------------------

  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      sensor->remove();
    }
  }

  //---------------------------
}
void Player::player_record(){
  //---------------------------
/*
  record = !record;
*/
  //---------------------------
}
void Player::player_lock(){
  //---------------------------

  //---------------------------
}


}
