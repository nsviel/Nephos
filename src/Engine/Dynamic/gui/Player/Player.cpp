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

  this->show_window = show_window;
  this->name = "Player";

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::run_panel(){
  utl::type::Element* element = dat_graph->get_selection();
  //---------------------------

  if(*show_window && element != nullptr){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel(element);

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Player::design_panel(utl::type::Element* element){
  //---------------------------

  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    if(set->player == nullptr) return;
    //Button player
    this->draw_player(set->player);
  }

  //---------------------------
}

//Player function
void Player::draw_player(dyn::player::Structure* ply){
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
void Player::player_slider(dyn::player::Structure* ply){
  //---------------------------

  ImVec2 width = ImGui::GetContentRegionAvail();
  ImGui::SetNextItemWidth(width.x);
  if(ImGui::SliderFloat("##player_slider", &ply->ts_cur, ply->ts_beg, ply->ts_end, "%.2f s", ImGuiSliderFlags_NoInput)){
    ply->player_query_ts(ply->ts_cur);
  }

  //---------------------------
}
void Player::player_start(dyn::player::Structure* ply){
  //---------------------------

  //If player start / pause button is appearing, allow keyboard control
  gui_control->run_control(ply);

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
void Player::player_stop(dyn::player::Structure* ply){
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
void Player::player_repeat(dyn::player::Structure* ply){
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
void Player::player_record(dyn::player::Structure* ply){
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
void Player::player_close(dyn::player::Structure* ply){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 100, 100, 255));
  if(ImGui::Button(ICON_FA_CIRCLE_XMARK "##399")){
    ply->player_close();
  }
  ImGui::PopStyleColor();

  //---------------------------
}
void Player::player_lock(dyn::player::Structure* ply){
  //---------------------------

  if(ply->locked){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_LOCK "##399")){
      ply->locked = false;
    }
    ImGui::PopStyleColor();
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_UNLOCK "##399")){
      ply->locked = true;
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}

}
