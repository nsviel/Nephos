#include "Player.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace dyn::gui{

//Constructor / Destructor
Player::Player(dyn::Node* node_dynamic, bool* show_window){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();

  this->dat_selection = node_data->get_dat_selection();
  this->gui_operation = new dyn::gui::Operation(node_dynamic);

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
    ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(250, FLT_MAX));
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

  this->design_player();
  gui_operation->design_operation();

  //---------------------------
}
void Player::design_player(){
  dat::base::Set* set = dat_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  this->player_slider(set);
  this->player_start(set);
  ImGui::SameLine();
  this->player_stop(set);
  ImGui::SameLine();
  this->player_repeat(set);
  ImGui::SameLine();
  this->player_record(set);
  ImGui::SameLine();
  this->player_close(set);
  ImGui::SameLine();
  this->player_lock(set);

  //---------------------------
  ImGui::Separator();
}

//Player function
void Player::player_slider(dat::base::Set* set){
  dyn::base::Player* player = &set->player;
  //---------------------------

  player->player_update();

  float width = ImGui::GetContentRegionAvail().x;
  ImGui::SetNextItemWidth(width);
  string time = "%.2f " + player->time;
  if(ImGui::SliderFloat("##player_slider", &player->ts_cur, player->ts_beg, player->ts_end, time.c_str(), ImGuiSliderFlags_NoInput)){
    player->player_query(player->ts_cur);
  }

  //---------------------------
}
void Player::player_start(dat::base::Set* set){
  dyn::base::Player* player = &set->player;
  //---------------------------

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

  //---------------------------
}
void Player::player_stop(dat::base::Set* set){
  dyn::base::Player* player = &set->player;
  //---------------------------

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

  //---------------------------
}
void Player::player_repeat(dat::base::Set* set){
  dyn::base::Player* player = &set->player;
  //---------------------------

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

  //---------------------------
}
void Player::player_record(dat::base::Set* set){
  dyn::base::Player* player = &set->player;
  //---------------------------

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

  //---------------------------
}
void Player::player_close(dat::base::Set* set){
  dyn::base::Player* player = &set->player;
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 100, 100, 255));
  if(ImGui::Button(ICON_FA_CIRCLE_XMARK "##399")){
    player->player_close();
  }
  ImGui::PopStyleColor();

  //---------------------------
}
void Player::player_lock(dat::base::Set* set){
  dyn::base::Player* player = &set->player;
  //---------------------------

  if(set->is_locked){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_LOCK "##399")){
      player->player_lock(false);
    }
    ImGui::PopStyleColor();
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_UNLOCK "##399")){
      player->player_lock(true);
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}

}
