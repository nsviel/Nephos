#include "Player.h"


namespace eng::kinect{

//Constructor / Destructor
Player::Player(){
  //---------------------------


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



}
