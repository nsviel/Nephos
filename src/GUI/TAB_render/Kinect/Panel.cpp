#include "Panel.h"

#include <Node/GUI.h>
#include <Engine/Engine.h>
#include <Utility/Node/Namespace.h>


namespace gui::kinect{

//Constructor / Destructor
Panel::Panel(GUI* gui, bool* show_window, string name) : gui::base::Panel(show_window, name){
  //---------------------------

  Engine* engine = gui->get_engine();
  eng::capture::Node* utl_capture = engine->get_eng_capture();
  eng::kinect::Kinect* kinect = utl_capture->get_kinect();

  this->kin_configuration = new gui::kinect::Capture(kinect);
  this->kin_playback = new gui::kinect::Playback(kinect);
  this->kin_recorder = new gui::kinect::Recorder(kinect);
  this->kin_player = new gui::kinect::Player(kinect);

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::design_panel(){
  //---------------------------

  kin_player->draw_player();
  if (ImGui::BeginTabBar("kinect_tab")){
    this->draw_tab_capture();
    this->draw_tab_playback();
    this->draw_tab_recorder();
    ImGui::EndTabBar();
  }

  //---------------------------
}

//Subfunction
void Panel::draw_tab_capture(){
  //---------------------------

  ImGui::SetNextItemWidth(100);
  if (ImGui::BeginTabItem("Capture##12323", NULL)){
    kin_configuration->kinect_configuration();
    ImGui::EndTabItem();
  }

  //---------------------------
}
void Panel::draw_tab_playback(){
  //---------------------------

  ImGui::SetNextItemWidth(100);
  if (ImGui::BeginTabItem("Playback##4567", NULL)){
    kin_playback->kinect_playback();
    ImGui::EndTabItem();
  }

  //---------------------------
}
void Panel::draw_tab_recorder(){
  //---------------------------

  ImGui::SetNextItemWidth(100);
  if (ImGui::BeginTabItem("Recorder##4567", NULL)){
    kin_recorder->kinect_recorder();
    ImGui::EndTabItem();
  }

  //---------------------------
}

}
