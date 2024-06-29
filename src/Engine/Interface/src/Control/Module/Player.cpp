#include "Player.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <Interface/Namespace.h>


namespace itf::control{

//Constructor / Destructor
Player::Player(itf::Node* node_interface){
  //---------------------------

  dat::Node* node_data = node_interface->get_node_data();
  dyn::Node* node_dynamic = node_interface->get_node_dynamic();

  this->dat_selection = node_data->get_dat_selection();
  this->dyn_player = node_dynamic->get_dyn_player();

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
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){

    //Tab key
    if(ImGui::IsKeyPressed(ImGuiKey_Space)){
      dyn_player->button_pause();
      break;
    }

    //Left arrow key
    if(ImGui::IsKeyPressed(ImGuiKey_LeftArrow)){
      //player->ts_forward = -1;
      break;
    }

    //Right arrow key
    if(ImGui::IsKeyPressed(ImGuiKey_RightArrow)){
      //player->ts_forward = 1;
      break;
    }
  }

  //---------------------------
}


}
