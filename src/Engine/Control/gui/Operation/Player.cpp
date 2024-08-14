#include "Player.h"

#include <Control/Namespace.h>
#include <imgui/core/imgui.h>


namespace ctl::gui{

//Constructor / Destructor
Player::Player(ctl::Node* node_control){
  //---------------------------

  this->ctl_struct = node_control->get_ctl_struct();
  this->ctl_player = node_control->get_ctl_player();

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
  if(ImGui::IsKeyPressed(ImGuiKey_Space)) ctl_player->make_pause();

  //Left arrow key
  if(ImGui::IsKeyPressed(ImGuiKey_LeftArrow)) ctl_player->make_forward();

  //Right arrow key
  if(ImGui::IsKeyPressed(ImGuiKey_RightArrow)) ctl_player->make_backward();

  //---------------------------
}


}
