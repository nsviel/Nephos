#include "Player.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>


namespace eng::k4n::gui{

//Constructor / Destructor
Player::Player(eng::k4n::Node* node_k4n, bool* show_window){
  //---------------------------

  this->node_k4n = node_k4n;
  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->gui_capture = new eng::k4n::gui::Capture(node_k4n);
  this->gui_playback = new eng::k4n::gui::Playback(node_k4n);
  this->gui_recorder = new eng::k4n::gui::Recorder(node_k4n);
  this->gui_master = new eng::k4n::gui::Master(node_k4n);
  this->gui_sensor = new eng::k4n::gui::Sensor(node_k4n);

  this->show_window = show_window;
  this->name = "Player";

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::run_panel(){
  eng::k4n::dev::Sensor* sensor = k4n_swarm->get_selected_sensor();
  //---------------------------

  if(*show_window && sensor != nullptr){
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
  eng::k4n::dev::Master* master = k4n_swarm->get_selected_master();
  //---------------------------

  //Master player
  this->draw_player(master);

  //Device info & configuration
  if(master != nullptr && ImGui::BeginTabBar("devices_tab##4567")){
    this->show_master_tab(master);

    //Master sensor tabs -> click = sensor selection
    for(int i=0; i< master->list_sensor.size(); i++){
      eng::k4n::dev::Sensor* sensor = *std::next( master->list_sensor.begin(), i);
      this->show_sensor_tab(sensor);
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}

//Player function
void Player::draw_player(eng::k4n::dev::Master* master){
  //---------------------------

  node_k4n->control();
  this->player_slider(master);

  this->player_start(master);
  ImGui::SameLine();
  this->player_stop(master);
  ImGui::SameLine();
  this->player_repeat(master);
  ImGui::SameLine();
  this->player_record(master);
  ImGui::SameLine();
  this->player_close(master);
  ImGui::SameLine();
  this->player_lock(master);

  //---------------------------
}
void Player::player_slider(eng::k4n::dev::Master* master){
  //---------------------------

  ImVec2 width = ImGui::GetContentRegionAvail();
  ImGui::SetNextItemWidth(width.x);
  if(ImGui::SliderFloat("##player_slider", &master->player.ts_cur, master->player.ts_beg, master->player.ts_end, "%.2f s", ImGuiSliderFlags_NoInput)){
    master->set_desired_timestamp(master->player.ts_cur);
  }

  //---------------------------
}
void Player::player_start(eng::k4n::dev::Master* master){
  //---------------------------

  //Play button -> if paused or not playing
  if(master->player.pause){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, 255));
    if(ImGui::Button(ICON_FA_PLAY "##player_start")){
      master->set_play();
    }
    ImGui::PopStyleColor();
  }
  //Pause button -> if not paused and playing
  else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(45, 133, 133, 255));
    if(ImGui::Button(ICON_FA_PAUSE "##player_pause")){
      master->set_pause(true);
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Player::player_stop(eng::k4n::dev::Master* master){
  //---------------------------

  if(!master->player.pause){
    //Player is running
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    if (ImGui::Button(ICON_FA_STOP "##37")){
      master->set_stop();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Player is stoped
    if (ImGui::Button(ICON_FA_STOP "##37")){
      master->set_stop();
    }
  }

  //---------------------------
}
void Player::player_repeat(eng::k4n::dev::Master* master){
  //---------------------------

  if(master->player.restart){
    //Repeat activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 133, 133, 255));
    if(ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      master->set_restart();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Repeat desactivated
    if (ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      master->set_restart();
    }
  }

  //---------------------------
}
void Player::player_record(eng::k4n::dev::Master* master){
  //---------------------------

  if(master->player.record){
    //Record activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    if (ImGui::Button(ICON_FA_CIRCLE "##37")){
      master->set_record();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Record desactivated
    if (ImGui::Button(ICON_FA_CIRCLE "##37")){
      master->set_record();
    }
  }

  //---------------------------
}
void Player::player_close(eng::k4n::dev::Master* master){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 100, 100, 255));
  if(ImGui::Button(ICON_FA_CIRCLE_XMARK "##399")){
    k4n_swarm->close_selected_sensor();
  }
  ImGui::PopStyleColor();

  //---------------------------
}
void Player::player_lock(eng::k4n::dev::Master* master){
  //---------------------------

  if(master->is_locked){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_LOCK "##399")){
      master->is_locked = false;
    }
    ImGui::PopStyleColor();
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 133, 40, 255));
    if(ImGui::Button(ICON_FA_UNLOCK "##399")){
      master->is_locked = true;
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}

//Device function
void Player::show_master_tab(eng::k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------

  string name = master->icon + "  " + "Master";
  if(ImGui::BeginTabItem(name.c_str(), NULL)){
    gui_master->show_master_info(master);
    ImGui::EndTabItem();
  }

  //---------------------------
}
void Player::show_sensor_tab(eng::k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  //---------------------------

  //Force tab open if another sensor selected
  ImGuiTabItemFlags flag = get_tab_flag(sensor);
  string name = sensor->icon + "  " + sensor->name;
  if(ImGui::BeginTabItem(name.c_str(), NULL, flag)){

    gui_sensor->show_sensor(sensor);
    gui_capture->show_sensor_configuration(sensor);
    gui_playback->show_sensor_configuration(sensor);
    //gui_recorder->show_sensor_recorder(sensor);

    ImGui::EndTabItem();
  }

  //---------------------------
}

//Subfunction
ImGuiTabItemFlags Player::get_tab_flag(eng::k4n::dev::Sensor* sensor){
  eng::k4n::dev::Master* master = sensor->master;
  //---------------------------

  ImGuiTabItemFlags flag = 0;
  static int UID = master->selected_entity->UID;
  if(master->is_selected_entity(sensor) && sensor->UID != UID){
    flag = ImGuiTabItemFlags_SetSelected;
    UID = master->selected_entity->UID;
  }

  //---------------------------
  return flag;
}

}
