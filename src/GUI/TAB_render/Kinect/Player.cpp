#include "Player.h"

#include <image/IconsFontAwesome5.h>
#include <Engine/Capture/Kinect/Thread/K4A_playback.h>
#include <Engine/Capture/Kinect/Device/K4A_swarm.h>


namespace gui::kinect{

//Constructor / Destructor
Player::Player(eng::kinect::Kinect* kinect){
  //---------------------------

  this->kinect = kinect;
  this->k4a_swarm = kinect->get_k4a_swarm();

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

      break;
    }

    //Right arrow key
    if(ImGui::IsKeyPressed(ImGuiKey_RightArrow)){

      break;
    }
  }

  //----------------------------
}
void Player::player_slider(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  eng::kinect::structure::Player* player = &k4a_device->player;
  bool is_playing = true;

  //Slider
  ImVec2 image_size = ImGui::GetContentRegionAvail();
  ImGui::SetNextItemWidth(image_size.x);
  if(ImGui::SliderFloat("###Slider_playback", &player->ts_cur, player->ts_beg, player->ts_end, "%.2f s")){
    k4a_device->k4a_replay->set_current_timestamp(player->ts_cur);
  }

  //---------------------------
}
void Player::player_start(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  eng::kinect::structure::Player* player = &k4a_device->player;
  ImU32 color = (player->pause || !player->play) ? IM_COL32(46, 133, 45, 255) : IM_COL32(133, 133, 0, 255);
  string icon = (player->pause || !player->play) ? (ICON_FA_PLAY "##36") : (ICON_FA_PAUSE "##36");
  ImGui::PushStyleColor(ImGuiCol_Button, color);
  if(ImGui::Button(icon.c_str())){
    if(!player->play){
      k4a_device->k4a_replay->set_current_timestamp(player->ts_beg);
      player->play = true;
      player->pause = false;
    }else{
      player->pause = !player->pause;
    }
  }
  ImGui::PopStyleColor(1);

  //---------------------------
}
void Player::player_stop(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  eng::kinect::structure::Player* player = &k4a_device->player;
  if(!player->pause) ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
  if (ImGui::Button(ICON_FA_STOP "##37")){
    k4a_device->k4a_replay->set_current_timestamp(k4a_device->player.ts_beg);
    player->restart = false;
    player->play = false;
    player->pause = false;
  }
  if(!player->pause) ImGui::PopStyleColor(1);

  //---------------------------
}
void Player::player_repeat(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  eng::kinect::structure::Player* player = &k4a_device->player;
  if(player->restart) ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 133, 133, 255));
  if (ImGui::Button(ICON_FA_REPEAT "##37")){
    player->restart = !player->restart;
  }
  if(player->restart) ImGui::PopStyleColor(1);

  //---------------------------
}
void Player::player_record(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  eng::kinect::structure::Player* player = &k4a_device->player;
  if(player->record) ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
  if (ImGui::Button(ICON_FA_CIRCLE "##37")){
    player->record = !player->record;
  }
  if(player->record) ImGui::PopStyleColor(1);

  //---------------------------
}

}
