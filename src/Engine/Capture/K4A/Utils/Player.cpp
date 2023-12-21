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
void Player::play(K4A_device* k4a_device){
  eng::kinect::structure::Player* player = &k4a_device->player;
  //---------------------------

  if(!player->play){
    player->play = true;
    player->pause = false;
  }else{
    player->pause = false;
  }

  //---------------------------
}
void Player::pause(K4A_device* k4a_device){
  eng::kinect::structure::Player* player = &k4a_device->player;
  //---------------------------

  player->pause = true;

  //---------------------------
}
void Player::stop(K4A_device* k4a_device){
  eng::kinect::structure::Player* player = &k4a_device->player;
  //---------------------------

  player->ts_seek = player->ts_beg;
  player->play = false;
  player->pause = true;

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

  ope_attribut->compute_MinMax(k4a_device->cloud.object);
  ope_transform->make_rotation_axe_X(k4a_device->cloud.object, value * 90);

  //---------------------------
}



}
