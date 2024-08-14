#include "Player.h"

#include <Control/Namespace.h>
#include <imgui/core/imgui.h>


namespace ctr::gui{

//Constructor / Destructor
Player::Player(ctr::Node* node_control){
  //---------------------------

  this->ctr_struct = node_control->get_ctr_struct();
  this->ctr_player = node_control->get_ctr_player();

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
  if(ImGui::IsKeyPressed(ImGuiKey_Space)) ctr_player->make_pause();

  //Left arrow key
  if(ImGui::IsKeyPressed(ImGuiKey_LeftArrow)) ctr_player->make_forward();

  //Right arrow key
  if(ImGui::IsKeyPressed(ImGuiKey_RightArrow)) ctr_player->make_backward();

  //---------------------------
}


}
