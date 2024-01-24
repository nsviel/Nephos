#include "Player.h"

#include <Engine/Engine.h>
#include <Engine/Capture/K4N/src/Thread/K4A_playback.h>
#include <image/IconsFontAwesome6.h>


namespace eng::k4n::gui{

//Constructor / Destructor
Player::Player(Engine* engine){
  //---------------------------

  eng::scene::Node* node_scene = engine->get_node_scene();
  eng::capture::Node* node_capture = engine->get_node_capture();

  this->sce_scene = node_scene->get_scene();
  this->k4a_node = node_capture->get_k4a_node();
  this->k4n_swarm = k4a_node->get_k4n_swarm();

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::draw_player(eng::k4n::dev::Master* master){
  //---------------------------

  this->player_control(master);
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

//Subfunction
void Player::player_control(eng::k4n::dev::Master* master){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    //Tab key
    if(ImGui::IsKeyPressed(ImGuiKey_Space)){
      master->set_pause(!master->player.pause);
      break;
    }

    //Left arrow key
    if(ImGui::IsKeyPressed(ImGuiKey_LeftArrow)){
      master->player.ts_forward = -1;
      break;
    }

    //Right arrow key
    if(ImGui::IsKeyPressed(ImGuiKey_RightArrow)){
      master->player.ts_forward = 1;
      break;
    }
  }

  //----------------------------
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

//Player button
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

}
