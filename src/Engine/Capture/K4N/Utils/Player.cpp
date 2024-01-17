#include "Player.h"


namespace k4n::utils{

//Constructor / Destructor
Player::Player(){
  //---------------------------

  this->ope_transform = new eng::ope::Transformation();
  this->ope_attribut = new eng::ope::Attribut();
  this->ope_operation = new eng::ope::Operation();

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::play(k4n::dev::Device* device){
  //---------------------------

  if(k4n::dev::Master* master = dynamic_cast<k4n::dev::Master*>(device)){
    if(!master->player.play){
      master->player.play = true;
      master->player.pause = false;
    }else{
      master->player.pause = false;
    }

    for(int i=0; i<master->list_sensor.size(); i++){
      k4n::dev::Sensor* sensor = *next(master->list_sensor.begin(), i);
      this->play(sensor);
    }
  }

  //---------------------------
}
void Player::play_(k4n::structure::Player* player){
  //---------------------------

  if(!player->play){
    player->play = true;
    player->pause = false;
  }else{
    player->pause = false;
  }

  //---------------------------
}
void Player::pause(k4n::dev::Sensor* k4n_sensor){
  k4n::structure::Player* player = &k4n_sensor->player;
  //---------------------------

  player->pause = true;

  //---------------------------
}
void Player::stop(k4n::dev::Sensor* k4n_sensor){
  k4n::structure::Player* player = &k4n_sensor->player;
  //---------------------------

  player->ts_seek = player->ts_beg;
  player->play = false;
  player->pause = true;

  //---------------------------
}
void Player::restart(k4n::dev::Sensor* k4n_sensor){
  k4n::structure::Player* player = &k4n_sensor->player;
  //---------------------------

  player->restart = !player->restart;

  //---------------------------
}
void Player::record(k4n::dev::Sensor* k4n_sensor){
  k4n::structure::Player* player = &k4n_sensor->player;
  //---------------------------

  player->record = !player->record;

  //---------------------------
}


}
