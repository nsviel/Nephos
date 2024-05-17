#include "Player.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n::dev{

//Constructor / Destructor
Player::Player(k4n::Node* node_k4n, k4n::dev::Master* master) : dyn::base::Player(master){
  //---------------------------

  this->gui_master = new k4n::gui::Master(node_k4n);

  this->master = master;
  this->time = "s";
  this->ts_beg = 0;
  this->ts_end = 100000;

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::player_stop(){
  //---------------------------

  //Pause playback thread
  this->play = false;
  this->pause = true;

  //Wait for pause
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      sensor->wait_thread();
    }
  }

  this->player_query_ts(ts_beg);

  //---------------------------
}
void Player::player_update(){
  //---------------------------

  //Search for min max timestamp
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
      if(i == 0){
        this->ts_beg = sensor->ts_beg;
        this->ts_end = sensor->ts_end;
        this->ts_duration = ts_end - ts_beg;
      }else{
        this->ts_beg = (ts_beg != -1) ? std::max(ts_beg, sensor->ts_beg) : sensor->ts_beg;
        this->ts_end = (ts_end != -1) ? std::min(ts_end, sensor->ts_end) : sensor->ts_end;
        this->ts_duration = ts_end - ts_beg;
      }
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
  this->ts_cur = value;
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

void Player::element_info(){
  //---------------------------

  gui_master->show_info(master);

  //---------------------------
  ImGui::Separator();
}
void Player::element_parameter(){
  //---------------------------

  gui_master->show_parameter(master);

  //---------------------------
  ImGui::Separator();
}

}
