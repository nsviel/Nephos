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
void Player::play(k4n::truc::K4A_device* k4a_device){
  k4n::structure::Player* player = &k4a_device->player;
  //---------------------------

  if(!player->play){
    player->play = true;
    player->pause = false;
  }else{
    player->pause = false;
  }

  //---------------------------
}
void Player::pause(k4n::truc::K4A_device* k4a_device){
  k4n::structure::Player* player = &k4a_device->player;
  //---------------------------

  player->pause = true;

  //---------------------------
}
void Player::stop(k4n::truc::K4A_device* k4a_device){
  k4n::structure::Player* player = &k4a_device->player;
  //---------------------------

  player->ts_seek = player->ts_beg;
  player->play = false;
  player->pause = true;

  //---------------------------
}
void Player::restart(k4n::truc::K4A_device* k4a_device){
  k4n::structure::Player* player = &k4a_device->player;
  //---------------------------

  player->restart = !player->restart;

  //---------------------------
}
void Player::record(k4n::truc::K4A_device* k4a_device){
  k4n::structure::Player* player = &k4a_device->player;
  //---------------------------

  player->record = !player->record;

  //---------------------------
}


}
