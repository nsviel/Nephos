#include "Player.h"

#include <Velodyne/Namespace.h>
#include <Utility/Namespace.h>
#include <Graph/Namespace.h>


namespace vld::gui{

//Constructor / Destructor
Player::Player(vld::structure::Main* vld_struct){
  //---------------------------

  this->vld_struct = vld_struct;
  this->vld_player = new vld::processing::Player(vld_struct);

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::design_player(){
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
  ImGui::Separator();
}

//Subfunction
void Player::player_slider(){
  //---------------------------

  ImVec2 width = ImGui::GetContentRegionAvail();
  ImGui::SetNextItemWidth(width.x);
  if(ImGui::SliderInt("##player_slider", &vld_struct->player.idx_cur, vld_struct->player.idx_beg, vld_struct->player.idx_end, "%d", ImGuiSliderFlags_NoInput)){
    vld_player->forward_index(vld_struct->player.idx_cur);
  }

  //---------------------------
}
void Player::player_start(){
  //---------------------------

  //Play button -> if paused or not playing
  if(vld_struct->player.pause){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(46, 100, 45, 255));
    if(ImGui::Button(ICON_FA_PLAY "##player_start")){
      vld_player->player_play();
    }
    ImGui::PopStyleColor(2);
  }
  //Pause button -> if not paused and playing
  else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(45, 133, 133, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(45, 100, 100, 255));
    if(ImGui::Button(ICON_FA_PAUSE "##player_pause")){
      vld_player->player_pause(true);
    }
    ImGui::PopStyleColor(2);
  }

  //---------------------------
}
void Player::player_stop(){
  //---------------------------

  if(!vld_struct->player.pause){
    //Player is running
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 45, 45, 255));
    if(ImGui::Button(ICON_FA_STOP "##37")){
      vld_player->player_stop();
    }
    ImGui::PopStyleColor(2);
  }
  else{
    //Player is stoped
    if(ImGui::Button(ICON_FA_STOP "##37")){
      vld_player->player_stop();
    }
  }

  //---------------------------
}
void Player::player_repeat(){
  //---------------------------

  if(vld_struct->player.restart){
    //Repeat activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 133, 133, 255));
    if(ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      vld_player->player_restart();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Repeat desactivated
    if(ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      vld_player->player_restart();
    }
  }

  //---------------------------
}
void Player::player_close(){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 100, 100, 255));
  if(ImGui::Button(ICON_FA_CIRCLE_XMARK "##399")){
    vld_player->player_close();
  }
  ImGui::PopStyleColor();

  //---------------------------
}
void Player::player_lock(){
  utl::type::Set* set = vld_struct->data.current_set;
  if(set == nullptr) return;
  //---------------------------

  if(set->is_locked){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_LOCK "##399")){
      set->is_locked = false;
    }
    ImGui::PopStyleColor();
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_UNLOCK "##399")){
      set->is_locked = true;
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}

}
