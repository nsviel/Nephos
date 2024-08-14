#include "Player.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <Control/Namespace.h>


namespace ctl{

//Constructor / Destructor
Player::Player(ctl::Node* node_control){
  //---------------------------

  dat::Node* node_data = node_control->get_node_data();
  dyn::Node* node_dynamic = node_control->get_node_dynamic();

  this->dat_selection = node_data->get_dat_selection();
  this->dyn_player = node_dynamic->get_dyn_player();

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::make_pause(){
  //---------------------------

  dyn_player->button_pause();

  //---------------------------
}
void Player::make_forward(){
  //---------------------------

  //player->ts_forward = -1;

  //---------------------------
}
void Player::make_backward(){
  //---------------------------

  //player->ts_forward = 1;

  //---------------------------
}

}
