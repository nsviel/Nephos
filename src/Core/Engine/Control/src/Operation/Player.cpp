#include "Player.h"

#include <Engine/Control/Namespace.h>
#include <Data/Namespace.h>


namespace ctr{

//Constructor / Destructor
Player::Player(ctr::Node* node_control){
  //---------------------------

  dat::Node* node_data = node_control->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();
  dat::ply::Node* node_player = node_data->get_node_player();

  this->gph_selection = node_graph->get_gph_selection();
  this->ply_button = node_player->get_ply_button();

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::make_pause(){
  //---------------------------

  ply_button->button_pause();

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
