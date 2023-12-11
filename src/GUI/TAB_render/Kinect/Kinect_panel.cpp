#include "Kinect_panel.h"

#include <Node/GUI.h>
#include <Utility/Node/Namespace.h>
#include <Utility/Capture/UTL_capture.h>
#include <Utility/Capture/UTL_kinect/Kinect.h>
#include <Utility/Capture/UTL_kinect/K4A_struct/Struct_k4a_swarm.h>
#include <Utility/Capture/UTL_kinect/K4A_device/K4A_swarm.h>
#include <Utility/Capture/UTL_kinect/K4A_device/K4A_configuration.h>


namespace gui::kinect{

//Constructor / Destructor
Kinect_panel::Kinect_panel(GUI* gui, bool* show_window, string name) : Panel(show_window, name){
  //---------------------------

  util::Node* utility = gui->get_utility();
  UTL_capture* utl_capture = utility->get_utl_capture();
  Kinect* kinect = utl_capture->get_kinect();

  this->kin_configuration = new gui::kinect::Configuration(kinect);
  this->kin_playback = new gui::kinect::Playback(kinect);
  this->kin_recorder = new gui::kinect::Recorder(kinect);

  //---------------------------
}
Kinect_panel::~Kinect_panel(){}

//Main function
void Kinect_panel::design_panel(){
  //---------------------------

  if (ImGui::BeginTabBar("kinect_tab")){
    this->draw_tab_capture();
    this->draw_tab_playback();
    this->draw_tab_recorder();
    ImGui::EndTabBar();
  }

  //---------------------------
}

//Subfunction
void Kinect_panel::draw_tab_capture(){
  //---------------------------

  ImGui::SetNextItemWidth(100);
  if (ImGui::BeginTabItem("Capture##12323", NULL)){
    kin_configuration->kinect_configuration();
    ImGui::EndTabItem();
  }

  //---------------------------
}
void Kinect_panel::draw_tab_playback(){
  //---------------------------

  ImGui::SetNextItemWidth(100);
  if (ImGui::BeginTabItem("Playback##4567", NULL)){
    kin_playback->kinect_playback();
    ImGui::EndTabItem();
  }

  //---------------------------
}
void Kinect_panel::draw_tab_recorder(){
  //---------------------------

  ImGui::SetNextItemWidth(100);
  if (ImGui::BeginTabItem("Recorder##4567", NULL)){
    kin_recorder->kinect_recorder();
    ImGui::EndTabItem();
  }

  //---------------------------
}

}
