#include "Player.h"

#include <Interface/Namespace.h>


namespace itf::gui{

//Constructor / Destructor
Player::Player(itf::Node* node_interface){
  //---------------------------

  this->itf_struct = node_interface->get_itf_struct();
  this->itf_player = node_interface->get_itf_player();

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::run_control(){
  //---------------------------

  this->control_keyboard();

  //---------------------------
}

//Keyboard
void Player::control_keyboard(){
  //----------------------------

  //Tab key
  if(ImGui::IsKeyPressed(ImGuiKey_Space)) itf_player->make_pause();

  //Left arrow key
  if(ImGui::IsKeyPressed(ImGuiKey_LeftArrow)) itf_player->make_forward();

  //Right arrow key
  if(ImGui::IsKeyPressed(ImGuiKey_RightArrow)) itf_player->make_backward();

  //---------------------------
}


}
