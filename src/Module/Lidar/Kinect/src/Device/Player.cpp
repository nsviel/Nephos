#include "Player.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n::dev{

//Constructor / Destructor
Player::Player(k4n::Node* node_k4n, k4n::dev::Master* master) : dyn::base::Player(master){
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
      this->ts_beg = (ts_beg != -1) ? std::max(ts_beg, sensor->ts_beg) : sensor->ts_beg;
      this->ts_end = (ts_end != -1) ? std::min(ts_end, sensor->ts_end) : sensor->ts_end;
      this->ts_duration = ts_end - ts_beg;
    }else{
      this->ts_beg = 0;
      this->ts_end = 0;
      this->ts_duration = 0;
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

}
