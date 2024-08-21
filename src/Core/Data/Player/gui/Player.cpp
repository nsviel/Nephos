#include "Player.h"

#include <Data/Player/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>
#include <imgui/core/imgui.h>


namespace dat::ply::gui{

//Constructor / Destructor
Player::Player(dat::ply::Node* node_player){
  //---------------------------

  this->ply_state = node_player->get_ply_state();
  this->ply_button = node_player->get_ply_button();
  //this->dyn_sensor = node_player->get_dyn_sensor();

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::design_player(utl::base::Element* element){
  //if(dyn_sensor->is_dynamic(element) == false) return;
  //---------------------------

  this->player_slider();
  this->player_play();
  ImGui::SameLine();
  this->player_stop();
  ImGui::SameLine();
  this->player_repeat();
  ImGui::SameLine();
  this->player_record();
  ImGui::SameLine();
  this->player_close();
  ImGui::SameLine();
  this->player_lock();

  //---------------------------
  ImGui::Separator();
}

//Player function
void Player::player_slider(){
  dat::base::Timestamp* timestamp = ply_state->get_timestamp();
  //---------------------------

  float width = ImGui::GetContentRegionAvail().x;
  ImGui::SetNextItemWidth(width);
  float current = timestamp->current;
  if(ImGui::SliderFloat("##player_slider", &current, timestamp->begin, timestamp->end, "%.2f s", ImGuiSliderFlags_NoInput)){
    ply_button->button_query(current);
  }

  //---------------------------
}
void Player::player_play(){
  dat::base::State* state = ply_state->get_state();
  //---------------------------

  //Play button -> if paused or not playing
  if(state->pause){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(46, 100, 45, 255));
    if(ImGui::Button(ICON_FA_PLAY "##player_play")){
      ply_button->button_play();
    }
    ImGui::PopStyleColor(2);
  }
  //Pause button -> if not paused and playing
  else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(45, 133, 133, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(45, 100, 100, 255));
    if(ImGui::Button(ICON_FA_PAUSE "##player_pause")){
      ply_button->button_pause();
    }
    ImGui::PopStyleColor(2);
  }

  //---------------------------
}
void Player::player_stop(){
  dat::base::State* state = ply_state->get_state();
  //---------------------------

  if(!state->pause){
    //Player is running
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 45, 45, 255));
    if(ImGui::Button(ICON_FA_STOP "##37")){
      ply_button->button_stop();
    }
    ImGui::PopStyleColor(2);
  }
  else{
    //Player is stoped
    if(ImGui::Button(ICON_FA_STOP "##37")){
      ply_button->button_stop();
    }
  }

  //---------------------------
}
void Player::player_repeat(){
  dat::base::State* state = ply_button->get_state();
  //---------------------------

  if(state->replay){
    //Repeat activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 133, 133, 255));
    if(ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      ply_button->button_replay();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Repeat desactivated
    if(ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      ply_button->button_replay();
    }
  }

  //---------------------------
}
void Player::player_record(){
  dat::base::State* state = ply_state->get_state();
  //---------------------------

  if(state->record){
    //Record activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    if(ImGui::Button(ICON_FA_CIRCLE "##37")){
      ply_button->button_record();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Record desactivated
    if(ImGui::Button(ICON_FA_CIRCLE "##37")){
      ply_button->button_record();
    }
  }

  //---------------------------
}
void Player::player_close(){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 100, 100, 255));
  if(ImGui::Button(ICON_FA_CIRCLE_XMARK "##399")){
    ply_button->button_close();
  }
  ImGui::PopStyleColor();

  //---------------------------
}
void Player::player_lock(){
  dat::base::State* state = ply_state->get_state();
  //---------------------------

  if(state->locked){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_LOCK "##399")){
      ply_button->button_lock(false);
    }
    ImGui::PopStyleColor();
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_UNLOCK "##399")){
      ply_button->button_lock(true);
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}

}
