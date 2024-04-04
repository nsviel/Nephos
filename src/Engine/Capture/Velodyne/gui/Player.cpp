#include "Player.h"

#include <Velodyne/Namespace.h>
#include <Utility/Namespace.h>
#include <Scene/Namespace.h>


namespace vld::gui{

//Constructor / Destructor
Player::Player(vld::Node* node_velodyne, bool* show_window){
  //---------------------------

  this->vld_struct = node_velodyne->get_vld_struct();
  this->vld_player = new vld::Player(vld_struct);

  this->show_window = show_window;
  this->name = "Player";

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::run_panel(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Player::design_panel(){
  //---------------------------

  this->draw_player();

  //---------------------------
}

//Player function
void Player::draw_player(){
  //---------------------------

  this->player_slider();

  this->player_start();
  ImGui::SameLine();
  this->player_stop();
  ImGui::SameLine();
  this->player_repeat();
  ImGui::SameLine();
  this->player_close();
  ImGui::SameLine();
  this->player_lock();

  //---------------------------
}
void Player::player_slider(){
  //---------------------------

  ImVec2 width = ImGui::GetContentRegionAvail();
  ImGui::SetNextItemWidth(width.x);
  if(ImGui::SliderInt("##player_slider", &vld_struct->player.idx_cur, vld_struct->player.idx_beg, vld_struct->player.idx_end, "%d", ImGuiSliderFlags_NoInput)){
    vld_player->compute_visibility();
  }

  //---------------------------
}
void Player::player_start(){
  //---------------------------

  //---------------------------
}
void Player::player_stop(){
  //---------------------------

  //---------------------------
}
void Player::player_repeat(){
  //---------------------------


  //---------------------------
}
void Player::player_close(){
  //---------------------------


  //---------------------------
}
void Player::player_lock(){
  //---------------------------


  //---------------------------
}

}
