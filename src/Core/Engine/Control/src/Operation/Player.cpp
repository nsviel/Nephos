#include "Player.h"

#include <Dynamic/Namespace.h>
#include <Control/Namespace.h>
#include <Data/Namespace.h>


namespace ctr{

//Constructor / Destructor
Player::Player(ctr::Node* node_control){
  //---------------------------

  dat::Node* node_data = node_control->get_node_data();
  dyn::Node* node_dynamic = node_control->get_node_dynamic();
  dat::gph::Node* node_graph = node_data->get_node_graph();
  dat::ply::Node* node_player = node_data->get_node_player();

  this->dat_selection = node_graph->get_dat_selection();
  this->dyn_player = node_player->get_dyn_player();

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
