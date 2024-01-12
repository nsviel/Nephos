#include "Panel.h"

#include <GUI.h>
#include <Engine/Engine.h>
#include <Utility/Namespace.h>


namespace gui::kinect{

//Constructor / Destructor
Panel::Panel(GUI* gui, bool* show_window, string name) : gui::base::Panel(show_window, name){
  //---------------------------

  Engine* engine = gui->get_engine();
  eng::capture::Node* node_capture = engine->get_node_capture();
  k4n::Node* node_kinect = node_capture->get_node_kinect();

  this->k4a_swarm = node_kinect->get_k4a_swarm();
  this->kin_capture = new gui::kinect::Capture(node_kinect);
  this->kin_playback = new gui::kinect::Playback(node_kinect);
  this->kin_recorder = new gui::kinect::Recorder(node_kinect);
  this->kin_player = new gui::kinect::Player(engine);
  this->kin_operation = new gui::kinect::Operation(node_kinect);

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  k4n::device::Device* k4a_device = k4a_swarm->get_selected_device();
  //---------------------------

  if(*show_window && k4a_device != nullptr){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(){
  //---------------------------

  kin_player->draw_player();
  this->show_info();

  kin_capture->kinect_configuration();
  kin_playback->kinect_playback();

  kin_operation->kinect_operation();
  kin_recorder->kinect_recorder();

  //---------------------------
}

//Subfunction
void Panel::show_info(){
  k4n::device::Device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

    ImGui::Separator();
  ImVec4 color = ImVec4(0.4f,1.0f,0.4f,1.0f);
  if(ImGui::BeginTable("Kinect_info##general", 2)){
    //Name
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Name"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4a_device->playback.filename.c_str());

    //Path
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Path"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4a_device->playback.path.c_str());

    //Duration
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Duration"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.2f s", k4a_device->player.duration);

    //Recording time
    if(k4a_device->player.record){
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Record"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%.2f s", k4a_device->recorder.ts_rec);
    }

    //Playback FPS
    if(k4a_device->device.is_playback){
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("FPS"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%.2f s", k4a_device->recorder.ts_rec);
    }

    ImGui::EndTable();
  }

  //---------------------------
}


}
