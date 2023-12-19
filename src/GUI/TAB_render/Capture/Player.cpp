#include "Player.h"

#include <image/IconsFontAwesome5.h>
#include <Engine/Capture/K4A/Thread/K4A_playback.h>
#include <Engine/Capture/K4A/Device/K4A_swarm.h>


namespace gui::kinect{

//Constructor / Destructor
Player::Player(eng::kinect::Kinect* kinect){
  //---------------------------

  this->kinect = kinect;
  this->k4a_swarm = kinect->get_k4a_swarm();
  this->k4a_player = new eng::kinect::Player();

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::draw_player(){
  //---------------------------

  this->player_control();
  this->player_slider();

  this->player_close();
  this->player_start();
  ImGui::SameLine();
  this->player_stop();
  ImGui::SameLine();
  this->player_repeat();
  ImGui::SameLine();
  this->player_record();

  //---------------------------
}

//Subfunction
void Player::player_control(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    //Tab key
    if(ImGui::IsKeyPressed(ImGuiKey_Space)){
      K4A_device* k4a_device = k4a_swarm->get_selected_device();
      k4a_device->player.pause = !k4a_device->player.pause;
      break;
    }

    //Left arrow key
    if(ImGui::IsKeyPressed(ImGuiKey_LeftArrow)){
      K4A_device* k4a_device = k4a_swarm->get_selected_device();
      k4a_device->player.ts_forward = -1;
      break;
    }

    //Right arrow key
    if(ImGui::IsKeyPressed(ImGuiKey_RightArrow)){
      K4A_device* k4a_device = k4a_swarm->get_selected_device();
      k4a_device->player.ts_forward = 1;
      break;
    }
  }

  //----------------------------
}
void Player::player_slider(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  ImVec2 available = ImGui::GetContentRegionAvail();
  ImGui::SetNextItemWidth(available.x);
  if(ImGui::SliderFloat("##player_slider", &k4a_device->player.ts_cur, k4a_device->player.ts_beg, k4a_device->player.ts_end, "%.2f s")){
    k4a_device->player.ts_seek = k4a_device->player.ts_cur;
  }

  //---------------------------
}

//Player button
void Player::player_close(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr || k4a_device->device.is_playback) return;
  //---------------------------

  //Close device button
  if(!k4a_device->device.is_playback){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 30, 30, 255));
    if(ImGui::Button("Close")){
      k4a_swarm->delete_device(k4a_device);
    }
    ImGui::PopStyleColor(2);
    ImGui::SameLine();
  }

  //---------------------------
}
void Player::player_start(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  if(k4a_device->player.pause || !k4a_device->player.play){
    //Play button
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, 255));
    if(ImGui::Button(ICON_FA_PLAY "##player_start")){
      k4a_player->start(k4a_device);
    }
    ImGui::PopStyleColor();
  }
  else{
    //Pause button
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(45, 133, 133, 255));
    if(ImGui::Button(ICON_FA_PAUSE "##player_pause")){
      k4a_player->pause(k4a_device);
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Player::player_stop(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr || !k4a_device->device.is_playback) return;
  //---------------------------

  if(!k4a_device->player.pause){
    //Player is running
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    if (ImGui::Button(ICON_FA_STOP "##37")){
      k4a_player->stop(k4a_device);
    }
    ImGui::PopStyleColor();
  }
  else{
    //Player is stoped
    if (ImGui::Button(ICON_FA_STOP "##37")){
      k4a_player->stop(k4a_device);
    }
  }

  //---------------------------
}
void Player::player_repeat(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr || !k4a_device->device.is_playback) return;
  //---------------------------

  if(k4a_device->player.restart){
    //Repeat activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 133, 133, 255));
    if(ImGui::Button(ICON_FA_REPEAT "##37")){
      k4a_player->restart(k4a_device);
    }
    ImGui::PopStyleColor();
  }
  else{
    //Repeat desactivated
    if (ImGui::Button(ICON_FA_REPEAT "##37")){
      k4a_player->restart(k4a_device);
    }
  }

  //---------------------------
}
void Player::player_record(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  if(k4a_device->player.record){
    //Record activated
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    if (ImGui::Button(ICON_FA_CIRCLE "##37")){
      k4a_player->record(k4a_device);
    }
    ImGui::PopStyleColor();
  }
  else{
    //Record desactivated
    if (ImGui::Button(ICON_FA_CIRCLE "##37")){
      k4a_player->record(k4a_device);
    }
  }

  //Recording time
  if(k4a_device->player.record){
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%.2f", k4a_device->recorder.ts_rec);
  }

  //---------------------------
}

}
