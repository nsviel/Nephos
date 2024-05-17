#include "Player.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace dyn::gui{

//Constructor / Destructor
Player::Player(dyn::Node* node_dynamic, bool* show_window){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();

  this->dat_graph = node_data->get_data_graph();
  this->gui_control = new dyn::gui::Control();
  this->ope_operation = new ope::Operation();

  this->show_window = show_window;
  this->name = "Player";

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::run_panel(){
  dat::base::Set* set = dat_graph->get_selected_set();
  //---------------------------
/*
  if(*show_window && set != nullptr && set->player->enable){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel(set);
      //element->info();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }
*/
  //---------------------------
}
void Player::design_panel(dat::base::Set* set){
  //---------------------------
/*
  this->draw_player(set->player);
  set->player_info();
*/
  //---------------------------
}

//Player function
void Player::draw_player(dyn::base::Player* player){
  //---------------------------

  this->player_slider(player);

  this->player_start(player);
  ImGui::SameLine();
  this->player_stop(player);
  ImGui::SameLine();
  this->player_repeat(player);
  ImGui::SameLine();
  this->player_record(player);
  ImGui::SameLine();
  this->player_close(player);
  ImGui::SameLine();
  this->player_lock(player);

  //---------------------------
}
void Player::player_slider(dyn::base::Player* player){
  //---------------------------
/*
  ImVec2 width = ImGui::GetContentRegionAvail();
  ImGui::SetNextItemWidth(width.x);
  if(ImGui::SliderFloat("##player_slider", &player->ts_cur, player->ts_beg, player->ts_end, "%.2f s", ImGuiSliderFlags_NoInput)){
    player->player_query_ts(player->ts_cur);
  }
*/
  //---------------------------
}
void Player::player_start(dyn::base::Player* player){
  //---------------------------
/*
  //If player start / pause button is appearing, allow keyboard control
  gui_control->run_control(player);

  //Play button -> if paused or not playing
  if(player->pause){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(46, 100, 45, 255));
    if(ImGui::Button(ICON_FA_PLAY "##player_start")){
      player->player_play();
    }
    ImGui::PopStyleColor(2);
  }
  //Pause button -> if not paused and playing
  else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(45, 133, 133, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(45, 100, 100, 255));
    if(ImGui::Button(ICON_FA_PAUSE "##player_pause")){
      player->player_pause();
    }
    ImGui::PopStyleColor(2);
  }
*/
  //---------------------------
}
void Player::player_stop(dyn::base::Player* player){
  //---------------------------
/*
  if(!player->pause){
    //Player is running
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 45, 45, 255));
    if(ImGui::Button(ICON_FA_STOP "##37")){
      player->player_stop();
    }
    ImGui::PopStyleColor(2);
  }
  else{
    //Player is stoped
    if(ImGui::Button(ICON_FA_STOP "##37")){
      player->player_stop();
    }
  }
*/
  //---------------------------
}
void Player::player_repeat(dyn::base::Player* player){
  //---------------------------
/*
  if(player->restart){
    //Repeat activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 133, 133, 255));
    if(ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      player->player_restart();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Repeat desactivated
    if(ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      player->player_restart();
    }
  }
*/
  //---------------------------
}
void Player::player_record(dyn::base::Player* player){
  //---------------------------
/*
  if(player->record){
    //Record activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    if(ImGui::Button(ICON_FA_CIRCLE "##37")){
      player->player_record();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Record desactivated
    if(ImGui::Button(ICON_FA_CIRCLE "##37")){
      player->player_record();
    }
  }
*/
  //---------------------------
}
void Player::player_close(dyn::base::Player* player){
  //---------------------------
/*
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 100, 100, 255));
  if(ImGui::Button(ICON_FA_CIRCLE_XMARK "##399")){
    player->player_close();
  }
  ImGui::PopStyleColor();
*/
  //---------------------------
}
void Player::player_lock(dyn::base::Player* player){
  //---------------------------
/*
  if(player->locked){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_LOCK "##399")){
      player->locked = false;
    }
    ImGui::PopStyleColor();
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_UNLOCK "##399")){
      player->locked = true;
    }
    ImGui::PopStyleColor();
  }
*/
  //---------------------------
}
void Player::draw_button(){
/*  dat::base::Entity* entity = dat_graph->get_selected_entity();
  if(entity == nullptr) return;
  //-------------------------------

  //Centered
  ImGui::SameLine();
  if(ImGui::Button("C##centerentity", ImVec2(20, 0))){
    ope_operation->center_object(entity);
  }

  //Rotation 90° around X axis
  ImGui::SameLine();
  if(ImGui::Button(ICON_FA_ARROWS_ROTATE "##xrotation")){
    ope_operation->make_rotation_X_90d(entity, 1);
  }
*/
  //-------------------------------
}

}
