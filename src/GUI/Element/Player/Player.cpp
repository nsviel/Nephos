#include "Player.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Scene/Namespace.h>


namespace gui::player{

//Constructor / Destructor
Player::Player(k4n::Node* node_k4n, bool* show_window){
  //---------------------------

  this->node_k4n = node_k4n;
  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->k4n_struct = node_k4n->get_k4n_struct();
  this->sce_set = new eng::scene::Set();
  this->gui_capture = new k4n::gui::Capture(node_k4n);
  this->gui_recorder = new k4n::gui::Recorder(node_k4n);
  this->gui_master = new k4n::gui::Master(node_k4n);
  this->gui_sensor = new k4n::gui::Sensor(node_k4n);
  this->gui_control = new k4n::gui::Control(node_k4n);

  this->show_window = show_window;
  this->name = "Player";

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::run_panel(){
  k4n::dev::Master* master = k4n_swarm->get_selected_master();
  //---------------------------

  if(*show_window && master != nullptr){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel(master);

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Player::design_panel(k4n::dev::Master* master){
  //---------------------------

  //Master player
  this->draw_player(master);

  //Device info & configuration
  if(master != nullptr && ImGui::BeginTabBar("devices_tab##4567")){
    this->show_master_tab(master);

    //Master sensor tabs -> click = sensor selection
    for(int i=0; i< master->list_entity.size(); i++){
      utl::type::Entity* entity = *next(master->list_entity.begin(), i);

      if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
        this->show_sensor_tab(sensor);
      }
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}

//Player function
void Player::draw_player(k4n::dev::Master* master){
  //---------------------------

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
void Player::player_slider(k4n::dev::Master* master){
  //---------------------------

  ImVec2 width = ImGui::GetContentRegionAvail();
  ImGui::SetNextItemWidth(width.x);
  if(ImGui::SliderFloat("##player_slider", &master->player.ts_cur, master->player.ts_beg, master->player.ts_end, "%.2f s", ImGuiSliderFlags_NoInput)){
    master->player_query_ts(master->player.ts_cur);
  }

  //---------------------------
}
void Player::player_start(k4n::dev::Master* master){
  //---------------------------

  //If player start / pause button is appearing, allow keyboard control
  gui_control->run_control();

  //Play button -> if paused or not playing
  if(master->player.pause){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(46, 100, 45, 255));
    if(ImGui::Button(ICON_FA_PLAY "##player_start")){
      master->player_play();
    }
    ImGui::PopStyleColor(2);
  }
  //Pause button -> if not paused and playing
  else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(45, 133, 133, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(45, 100, 100, 255));
    if(ImGui::Button(ICON_FA_PAUSE "##player_pause")){
      master->player_pause(true);
    }
    ImGui::PopStyleColor(2);
  }

  //---------------------------
}
void Player::player_stop(k4n::dev::Master* master){
  //---------------------------

  if(!master->player.pause){
    //Player is running
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 45, 45, 255));
    if(ImGui::Button(ICON_FA_STOP "##37")){
      master->player_stop();
    }
    ImGui::PopStyleColor(2);
  }
  else{
    //Player is stoped
    if(ImGui::Button(ICON_FA_STOP "##37")){
      master->player_stop();
    }
  }

  //---------------------------
}
void Player::player_repeat(k4n::dev::Master* master){
  //---------------------------

  if(master->player.restart){
    //Repeat activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 133, 133, 255));
    if(ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      master->player_restart();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Repeat desactivated
    if(ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      master->player_restart();
    }
  }

  //---------------------------
}
void Player::player_record(k4n::dev::Master* master){
  //---------------------------

  if(master->player.record){
    //Record activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    if(ImGui::Button(ICON_FA_CIRCLE "##37")){
      master->player_record();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Record desactivated
    if(ImGui::Button(ICON_FA_CIRCLE "##37")){
      master->player_record();
    }
  }

  //---------------------------
}
void Player::player_close(k4n::dev::Master* master){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 100, 100, 255));
  if(ImGui::Button(ICON_FA_CIRCLE_XMARK "##399")){
    master->player_close();
  }
  ImGui::PopStyleColor();

  //---------------------------
}
void Player::player_lock(k4n::dev::Master* master){
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
void Player::show_master_tab(k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------

  string name = master->icon + "  " + "Master";
  ImGui::SetNextItemWidth(90);
  if(ImGui::BeginTabItem(name.c_str(), NULL)){
    gui_master->show_master_info(master);
    ImGui::EndTabItem();
  }

  //---------------------------
}
void Player::show_sensor_tab(k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  //---------------------------

  //Force tab open if another sensor selected
  string name = sensor->icon + "  " + sensor->name;
  ImGui::SetNextItemWidth(90);
  if(ImGui::BeginTabItem(name.c_str(), NULL)){

    gui_sensor->show_sensor(sensor);
    //gui_recorder->show_sensor_recorder(sensor);

    ImGui::EndTabItem();
  }

  //---------------------------
}

}
