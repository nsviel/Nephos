#include "Player.h"

#include <Engine/Engine.h>
#include <Engine/Capture/K4A/Thread/K4A_playback.h>
#include <Engine/Capture/K4A/Device/K4A_swarm.h>
#include <image/IconsFontAwesome6.h>


namespace gui::kinect{

//Constructor / Destructor
Player::Player(Engine* engine){
  //---------------------------

  eng::scene::Node* node_scene = engine->get_node_scene();
  eng::capture::Node* node_capture = engine->get_node_capture();

  this->sce_scene = node_scene->get_scene();
  this->kinect = node_capture->get_kinect();
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

  this->player_start();
  ImGui::SameLine();
  this->player_stop();
  ImGui::SameLine();
  this->player_repeat();
  ImGui::SameLine();
  this->player_record();
  ImGui::SameLine();
  this->player_rotation();
  ImGui::SameLine();
  this->player_close();

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
void Player::player_start(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  //Play button -> if paused or not playing
  if(k4a_device->player.pause){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, 255));
    if(ImGui::Button(ICON_FA_PLAY "##player_start")){
      k4a_player->play(k4a_device);
    }
    ImGui::PopStyleColor();
  }
  //Pause button -> if not paused and playing
  else{
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
    if(ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
      k4a_player->restart(k4a_device);
    }
    ImGui::PopStyleColor();
  }
  else{
    //Repeat desactivated
    if (ImGui::Button(ICON_FA_ARROW_ROTATE_RIGHT "##37")){
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

  //---------------------------
}
void Player::player_rotation(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(100, 45, 133, 255));
  if(ImGui::Button(ICON_FA_ARROWS_ROTATE "##398")){
    k4a_player->rotation(k4a_device, 1);
  }
  ImGui::PopStyleColor();

  //---------------------------
}
void Player::player_close(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 100, 100, 255));
  if(ImGui::Button(ICON_FA_CIRCLE_XMARK "##399")){
    sce_scene->delete_entity(k4a_device);
  }
  ImGui::PopStyleColor();

  //---------------------------
}

}
