#include "Player.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace dyn::gui{

//Constructor / Destructor
Player::Player(dyn::Node* node_dynamic, bool* show_window){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();

  this->dyn_player = node_dynamic->get_dyn_player();
  this->dat_selection = node_data->get_dat_selection();
  this->gui_operation = new dyn::gui::Operation(node_dynamic);

  this->show_window = show_window;
  this->name = "Player";

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

  //player->manage_update();

  float width = ImGui::GetContentRegionAvail().x;
  ImGui::SetNextItemWidth(width);
  float current = timestamp->current;
  if(ImGui::SliderFloat("##player_slider", &current, timestamp->begin, timestamp->end, "%.2f s", ImGuiSliderFlags_NoInput)){
    //player->manage_query(current);
  }

  //---------------------------
}
void Player::player_start(){
  dyn::player::State* state = dyn_player->get_state();
  //---------------------------

  //Play button -> if paused or not playing
  if(state->pause){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(46, 100, 45, 255));
    if(ImGui::Button(ICON_FA_PLAY "##player_start")){
      dyn_player->player_play();
    }
    ImGui::PopStyleColor(2);
  }
  //Pause button -> if not paused and playing
  else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(45, 133, 133, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(45, 100, 100, 255));
    if(ImGui::Button(ICON_FA_PAUSE "##player_pause")){
      dyn_player->player_pause();
    }
    ImGui::PopStyleColor(2);
  }

  //---------------------------
}
void Player::player_stop(){
  dyn::player::State* state = dyn_player->get_state();
  //---------------------------

  if(!state->pause){
    //Player is running
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 45, 45, 255));
    if(ImGui::Button(ICON_FA_STOP "##37")){
      dyn_player->player_stop();
    }
    ImGui::PopStyleColor(2);
  }
  else{
    //Player is stoped
    if(ImGui::Button(ICON_FA_STOP "##37")){
      dyn_player->player_stop();
    }
  }

  //---------------------------
}
void Player::player_repeat(){
  dyn::player::State* state = dyn_player->get_state();
  //---------------------------

  if(state->restart){
    //Repeat activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 133, 133, 255));
    if(ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      dyn_player->player_restart();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Repeat desactivated
    if(ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      dyn_player->player_restart();
    }
  }

  //---------------------------
}
void Player::player_record(){
  dyn::player::State* state = dyn_player->get_state();
  //---------------------------

  if(state->record){
    //Record activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    if(ImGui::Button(ICON_FA_CIRCLE "##37")){
      dyn_player->player_record();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Record desactivated
    if(ImGui::Button(ICON_FA_CIRCLE "##37")){
      dyn_player->player_record();
    }
  }

  //---------------------------
}
void Player::player_close(){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 100, 100, 255));
  if(ImGui::Button(ICON_FA_CIRCLE_XMARK "##399")){
    dyn_player->player_close();
  }
  ImGui::PopStyleColor();

  //---------------------------
}
void Player::player_lock(){
  dyn::player::State* state = dyn_player->get_state();
  //---------------------------

  if(state->locked){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_LOCK "##399")){
      dyn_player->player_lock(false);
    }
    ImGui::PopStyleColor();
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_UNLOCK "##399")){
      dyn_player->player_lock(true);
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}

}
