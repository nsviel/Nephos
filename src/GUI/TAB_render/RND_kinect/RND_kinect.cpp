#include "RND_kinect.h"

#include <GUI.h>
#include <Utility.h>
#include <UTL_capture/UTL_capture.h>
#include <UTL_capture/UTL_kinect/Kinect.h>
#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_swarm.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_swarm.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_configuration.h>
#include <RND_kinect/KIN_configuration.h>
#include <RND_kinect/RND_capture.h>
#include <RND_kinect/KIN_playback.h>
#include <RND_kinect/KIN_recorder.h>


//Constructor / Destructor
RND_kinect::RND_kinect(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  Utility* utility = gui->get_utility();
  UTL_capture* utl_capture = utility->get_utl_capture();
  Kinect* kinect = utl_capture->get_kinect();

  this->kin_configuration = new KIN_configuration(kinect);
  this->kin_playback = new KIN_playback(kinect);
  this->kin_recorder = new KIN_recorder(kinect);

  //---------------------------
}
RND_kinect::~RND_kinect(){}

//Main function
void RND_kinect::design_panel(){
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
void RND_kinect::draw_tab_capture(){
  //---------------------------

  ImGui::SetNextItemWidth(100);
  if (ImGui::BeginTabItem("Capture##12323", NULL)){
    kin_configuration->kinect_configuration();
    ImGui::EndTabItem();
  }

  //---------------------------
}
void RND_kinect::draw_tab_playback(){
  //---------------------------

  ImGui::SetNextItemWidth(100);
  if (ImGui::BeginTabItem("Playback##4567", NULL)){
    kin_playback->kinect_playback();
    ImGui::EndTabItem();
  }

  //---------------------------
}
void RND_kinect::draw_tab_recorder(){
  //---------------------------

  ImGui::SetNextItemWidth(100);
  if (ImGui::BeginTabItem("Recorder##4567", NULL)){
    kin_recorder->kinect_recorder();
    ImGui::EndTabItem();
  }

  //---------------------------
}
