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
      element->info();

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
    set->player->gui_info();
  }
  else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    dat::base::Set* set = entity->set_parent;
    if(set->player == nullptr) return;
    //Button player
    this->draw_player(set->player);
    set->player->gui_info();
  }

  //---------------------------
}

//Player function
void Player::draw_player(dyn::base::Player* ply){
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
void Player::player_slider(dyn::base::Player* ply){
  //---------------------------

  ImVec2 width = ImGui::GetContentRegionAvail();
  ImGui::SetNextItemWidth(width.x);
  float& ts_cur = ply->get_ts_cur();
  float& ts_beg = ply->get_ts_beg();
  float& ts_end = ply->get_ts_end();
  if(ImGui::SliderFloat("##player_slider", &ts_cur, ts_beg, ts_end, "%.2f s", ImGuiSliderFlags_NoInput)){
    ply->player_query_ts(ts_cur);
  }

  //---------------------------
}
void Player::player_start(dyn::base::Player* ply){
  //---------------------------

  //If player start / pause button is appearing, allow keyboard control
  gui_control->run_control(ply);

  //Play button -> if paused or not playing
  bool& is_pause = ply->get_state_pause();
  if(is_pause){
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
      ply->player_pause();
    }
    ImGui::PopStyleColor(2);
  }

  //---------------------------
}
void Player::player_stop(dyn::base::Player* ply){
  //---------------------------

  bool& is_pause = ply->get_state_pause();
  if(!is_pause){
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
void Player::player_repeat(dyn::base::Player* ply){
  //---------------------------

  bool& is_restart = ply->get_state_restart();
  if(is_restart){
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
void Player::player_record(dyn::base::Player* ply){
  //---------------------------

  bool& is_record = ply->get_state_record();
  if(is_record){
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
void Player::player_close(dyn::base::Player* ply){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 100, 100, 255));
  if(ImGui::Button(ICON_FA_CIRCLE_XMARK "##399")){
    ply->player_close();
  }
  ImGui::PopStyleColor();

  //---------------------------
}
void Player::player_lock(dyn::base::Player* ply){
  //---------------------------

  bool& is_locked = ply->get_state_locked();
  if(is_locked){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_LOCK "##399")){
      is_locked = false;
    }
    ImGui::PopStyleColor();
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_UNLOCK "##399")){
      is_locked = true;
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}

}
