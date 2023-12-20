#include "Player.h"


namespace eng::kinect{

//Constructor / Destructor
Player::Player(){
  //---------------------------

  this->ope_transform = new eng::ope::Transformation();
  this->ope_attribut = new eng::ope::Attribut();

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::start(K4A_device* k4a_device){
  eng::kinect::structure::Player* player = &k4a_device->player;
  //---------------------------

  if(!player->play){
    player->ts_seek = player->ts_beg;
    player->play = true;
    player->pause = false;
  }else{
    player->pause = !player->pause;
  }

  //---------------------------
}
void Player::pause(K4A_device* k4a_device){
  eng::kinect::structure::Player* player = &k4a_device->player;
  //---------------------------

  if(!player->play){
    player->ts_seek = player->ts_beg;
    player->play = true;
    player->pause = false;
  }else{
    player->pause = !player->pause;
  }

  //---------------------------
}
void Player::stop(K4A_device* k4a_device){
  eng::kinect::structure::Player* player = &k4a_device->player;
  //---------------------------

  player->ts_seek = player->ts_beg;
  player->restart = false;
  player->play = false;
  player->pause = false;

  //---------------------------
}
void Player::restart(K4A_device* k4a_device){
  eng::kinect::structure::Player* player = &k4a_device->player;
  //---------------------------

  player->restart = !player->restart;

  //---------------------------
}
void Player::record(K4A_device* k4a_device){
  eng::kinect::structure::Player* player = &k4a_device->player;
  //---------------------------

  player->record = !player->record;

  //---------------------------
}
void Player::rotation(K4A_device* k4a_device, int value){
  //---------------------------

  ope_attribut->compute_MinMax(k4a_device->cloud.object);say(k4a_device->cloud.object.COM);
  ope_transform->make_rotation(k4a_device->cloud.object, vec3(value * 90, 0, 0));

  //---------------------------
}



}
