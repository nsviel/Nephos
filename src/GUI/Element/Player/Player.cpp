#include "Player.h"

#include <GUI/Namespace.h>


namespace gui::element{

//Constructor / Destructor
Player::Player(bool* show_window){
  //---------------------------

  this->player_control = new gui::player::Control();

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::draw_player(gui::player::Structure* ply){
  //---------------------------

  this->player_slider(ply);

  this->player_start(ply);
  ImGui::SameLine();
  this->player_stop(ply);
  ImGui::SameLine();
  this->player_repeat(ply);
  ImGui::SameLine();
  this->player_record(ply);
  ImGui::SameLine();
  this->player_close(ply);
  ImGui::SameLine();
  this->player_lock(ply);

  //---------------------------
}

//Player function
void Player::player_slider(gui::player::Structure* ply){
  //---------------------------

  ImVec2 width = ImGui::GetContentRegionAvail();
  ImGui::SetNextItemWidth(width.x);
  if(ImGui::SliderFloat("##player_slider", &ply->ts_cur, ply->ts_beg, ply->ts_end, "%.2f s", ImGuiSliderFlags_NoInput)){
    ply->player_query_ts(ply->ts_cur);
  }

  //---------------------------
}
void Player::player_start(gui::player::Structure* ply){
  //---------------------------

  //If player start / pause button is appearing, allow keyboard control
  player_control->run_control(ply);

  //Play button -> if paused or not playing
  if(ply->pause){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(46, 100, 45, 255));
    if(ImGui::Button(ICON_FA_PLAY "##player_start")){
      ply->player_play();
    }
    ImGui::PopStyleColor(2);
  }
  //Pause button -> if not paused and playing
  else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(45, 133, 133, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(45, 100, 100, 255));
    if(ImGui::Button(ICON_FA_PAUSE "##player_pause")){
      ply->player_pause(true);
    }
    ImGui::PopStyleColor(2);
  }

  //---------------------------
}
void Player::player_stop(gui::player::Structure* ply){
  //---------------------------

  if(!ply->pause){
    //Player is running
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 45, 45, 255));
    if(ImGui::Button(ICON_FA_STOP "##37")){
      ply->player_stop();
    }
    ImGui::PopStyleColor(2);
  }
  else{
    //Player is stoped
    if(ImGui::Button(ICON_FA_STOP "##37")){
      ply->player_stop();
    }
  }

  //---------------------------
}
void Player::player_repeat(gui::player::Structure* ply){
  //---------------------------

  if(ply->restart){
    //Repeat activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 133, 133, 255));
    if(ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      ply->player_restart();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Repeat desactivated
    if(ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      ply->player_restart();
    }
  }

  //---------------------------
}
void Player::player_record(gui::player::Structure* ply){
  //---------------------------

  if(ply->record){
    //Record activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    if(ImGui::Button(ICON_FA_CIRCLE "##37")){
      ply->player_record();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Record desactivated
    if(ImGui::Button(ICON_FA_CIRCLE "##37")){
      ply->player_record();
    }
  }

  //---------------------------
}
void Player::player_close(gui::player::Structure* ply){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 100, 100, 255));
  if(ImGui::Button(ICON_FA_CIRCLE_XMARK "##399")){
    ply->player_close();
  }
  ImGui::PopStyleColor();

  //---------------------------
}
void Player::player_lock(gui::player::Structure* ply){
  //---------------------------

  if(ply->set->is_locked){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_LOCK "##399")){
      ply->set->is_locked = false;
    }
    ImGui::PopStyleColor();
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_UNLOCK "##399")){
      ply->set->is_locked = true;
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}

}
