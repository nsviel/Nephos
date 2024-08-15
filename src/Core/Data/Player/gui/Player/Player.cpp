#include "Player.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat::ply::gui{

//Constructor / Destructor
Player::Player(dyn::Node* node_dynamic){
  //---------------------------

  this->dyn_player = node_dynamic->get_dyn_player();
  this->dyn_sensor = node_dynamic->get_dyn_sensor();

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::design_player(utl::base::Element* element){
  if(dyn_sensor->is_dynamic(element) == false) return;
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
  dyn::base::Timestamp* timestamp = dyn_player->get_timestamp();
  //---------------------------

  float width = ImGui::GetContentRegionAvail().x;
  ImGui::SetNextItemWidth(width);
  float current = timestamp->current;
  if(ImGui::SliderFloat("##player_slider", &current, timestamp->begin, timestamp->end, "%.2f s", ImGuiSliderFlags_NoInput)){
    dyn_player->button_query(current);
  }

  //---------------------------
}
void Player::player_play(){
  dyn::base::State* state = dyn_player->get_state();
  //---------------------------

  //Play button -> if paused or not playing
  if(state->pause){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(46, 100, 45, 255));
    if(ImGui::Button(ICON_FA_PLAY "##player_play")){
      dyn_player->button_play();
    }
    ImGui::PopStyleColor(2);
  }
  //Pause button -> if not paused and playing
  else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(45, 133, 133, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(45, 100, 100, 255));
    if(ImGui::Button(ICON_FA_PAUSE "##player_pause")){
      dyn_player->button_pause();
    }
    ImGui::PopStyleColor(2);
  }

  //---------------------------
}
void Player::player_stop(){
  dyn::base::State* state = dyn_player->get_state();
  //---------------------------

  if(!state->pause){
    //Player is running
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 45, 45, 255));
    if(ImGui::Button(ICON_FA_STOP "##37")){
      dyn_player->button_stop();
    }
    ImGui::PopStyleColor(2);
  }
  else{
    //Player is stoped
    if(ImGui::Button(ICON_FA_STOP "##37")){
      dyn_player->button_stop();
    }
  }

  //---------------------------
}
void Player::player_repeat(){
  dyn::base::State* state = dyn_player->get_state();
  //---------------------------

  if(state->replay){
    //Repeat activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 133, 133, 255));
    if(ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      dyn_player->button_replay();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Repeat desactivated
    if(ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      dyn_player->button_replay();
    }
  }

  //---------------------------
}
void Player::player_record(){
  dyn::base::State* state = dyn_player->get_state();
  //---------------------------

  if(state->record){
    //Record activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    if(ImGui::Button(ICON_FA_CIRCLE "##37")){
      dyn_player->button_record();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Record desactivated
    if(ImGui::Button(ICON_FA_CIRCLE "##37")){
      dyn_player->button_record();
    }
  }

  //---------------------------
}
void Player::player_close(){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 100, 100, 255));
  if(ImGui::Button(ICON_FA_CIRCLE_XMARK "##399")){
    dyn_player->button_close();
  }
  ImGui::PopStyleColor();

  //---------------------------
}
void Player::player_lock(){
  dyn::base::State* state = dyn_player->get_state();
  //---------------------------

  if(state->locked){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_LOCK "##399")){
      dyn_player->button_lock(false);
    }
    ImGui::PopStyleColor();
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_UNLOCK "##399")){
      dyn_player->button_lock(true);
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}

}
