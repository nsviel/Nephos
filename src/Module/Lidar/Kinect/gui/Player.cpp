#include "Player.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Player::Player(k4n::Node* node_k4n){
  //---------------------------

  this->node_k4n = node_k4n;
  this->gui_capture = new k4n::gui::Capture(node_k4n);
  this->gui_playback = new k4n::gui::Playback(node_k4n);

  this->item_width = 100;

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::show_info(k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------

  gui_capture->show_list_device(master);

  //---------------------------
}
void Player::show_parameter(k4n::dev::Master* master){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(39, 74, 90, 255));
  ImGui::PushStyleColor(ImGuiCol_TabHovered, IM_COL32(54, 112, 131, 255));
  ImGui::PushStyleColor(ImGuiCol_TabActive, IM_COL32(44, 101, 131, 255));
  if(ImGui::BeginTabBar("master_option##tab")){
    ImGui::SetNextItemWidth(75);
    if(ImGui::BeginTabItem("Operation##tab_item", NULL)){
      this->show_transformation_mode(master);
      ImGui::EndTabItem();
    }

    gui_capture->show_info_master(master);

    ImGui::EndTabBar();
  }
  ImGui::PopStyleColor(3);

  //---------------------------
}

//Subfunction
void Player::show_transformation_mode(k4n::dev::Master* master){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Transformation");

  ImGui::RadioButton("Depth to color", &master->config.depth.transformation_mode, k4n::depth::DEPTH_TO_COLOR);
  ImGui::SameLine();
  ImGui::RadioButton("Color to depth", &master->config.depth.transformation_mode, k4n::depth::COLOR_TO_DEPTH);

  //---------------------------
  ImGui::Separator();
}

}
