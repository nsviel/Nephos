#include "Player.h"

#include <Engine/Engine.h>
#include <Engine/Capture/K4N/Thread/K4A_playback.h>
#include <image/IconsFontAwesome6.h>


namespace gui::kinect{

//Constructor / Destructor
Player::Player(Engine* engine){
  //---------------------------

  eng::scene::Node* node_scene = engine->get_node_scene();
  eng::capture::Node* node_capture = engine->get_node_capture();

  this->sce_scene = node_scene->get_scene();
  this->node_kinect = node_capture->get_node_kinect();
  this->k4n_swarm = node_kinect->get_k4n_swarm();

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::draw_player(k4n::dev::Device* device){
  //---------------------------

  this->player_control(device);
  this->player_slider(device);

  this->player_start(device);
  ImGui::SameLine();
  this->player_stop(device);
  ImGui::SameLine();
  this->player_repeat(device);
  ImGui::SameLine();
  this->player_record(device);
  ImGui::SameLine();
  this->player_close(device);

  //---------------------------
}

//Subfunction
void Player::player_control(k4n::dev::Device* device){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    //Tab key
    if(ImGui::IsKeyPressed(ImGuiKey_Space)){
      device->set_pause(!device->player.pause);
      break;
    }

    //Left arrow key
    if(ImGui::IsKeyPressed(ImGuiKey_LeftArrow)){
      device->player.ts_forward = -1;
      break;
    }

    //Right arrow key
    if(ImGui::IsKeyPressed(ImGuiKey_RightArrow)){
      device->player.ts_forward = 1;
      break;
    }
  }

  //----------------------------
}
void Player::player_slider(k4n::dev::Device* device){
  //---------------------------

  ImVec2 available = ImGui::GetContentRegionAvail();
  ImGui::SetNextItemWidth(available.x);
  if(ImGui::SliderFloat("##player_slider", &device->player.ts_cur, device->player.ts_beg, device->player.ts_end, "%.2f s", ImGuiSliderFlags_NoInput)){
    device->set_desired_timestamp(device->player.ts_cur);
  }

  //---------------------------
}

//Player button
void Player::player_start(k4n::dev::Device* device){
  //---------------------------

  //Play button -> if paused or not playing
  if(device->player.pause){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, 255));
    if(ImGui::Button(ICON_FA_PLAY "##player_start")){
      device->set_play();
    }
    ImGui::PopStyleColor();
  }
  //Pause button -> if not paused and playing
  else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(45, 133, 133, 255));
    if(ImGui::Button(ICON_FA_PAUSE "##player_pause")){
      device->set_pause(true);
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Player::player_stop(k4n::dev::Device* device){
  //---------------------------

  if(!device->player.pause){
    //Player is running
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    if (ImGui::Button(ICON_FA_STOP "##37")){
      device->set_stop();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Player is stoped
    if (ImGui::Button(ICON_FA_STOP "##37")){
      device->set_stop();
    }
  }

  //---------------------------
}
void Player::player_repeat(k4n::dev::Device* device){
  //---------------------------

  if(device->player.restart){
    //Repeat activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 133, 133, 255));
    if(ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      device->set_restart();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Repeat desactivated
    if (ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      device->set_restart();
    }
  }

  //---------------------------
}
void Player::player_record(k4n::dev::Device* device){
  //---------------------------

  if(device->player.record){
    //Record activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    if (ImGui::Button(ICON_FA_CIRCLE "##37")){
      device->set_record();
    }
    ImGui::PopStyleColor();
  }
  else{
    //Record desactivated
    if (ImGui::Button(ICON_FA_CIRCLE "##37")){
      device->set_record();
    }
  }

  //---------------------------
}
void Player::player_close(k4n::dev::Device* device){
  k4n::dev::Sensor* k4n_sensor = k4n_swarm->get_selected_sensor();
  if(k4n_sensor == nullptr) return;
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 100, 100, 255));
  if(ImGui::Button(ICON_FA_CIRCLE_XMARK "##399")){
    sce_scene->delete_entity(k4n_sensor);
  }
  ImGui::PopStyleColor();

  //---------------------------
}

}
