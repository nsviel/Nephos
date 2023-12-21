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

  this->kin_capture = new gui::kinect::Capture(kinect);
  this->kin_playback = new gui::kinect::Playback(kinect);
  this->kin_recorder = new gui::kinect::Recorder(kinect);
  this->kin_player = new gui::kinect::Player(kinect);
  this->kin_operation = new gui::kinect::Operation(kinect);

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::design_panel(){
  //---------------------------

  kin_player->draw_player();
  kin_capture->kinect_configuration();
  kin_playback->kinect_playback();
  kin_operation->kinect_operation();
  kin_recorder->kinect_recorder();
  
  //---------------------------
}

//Subfunction



}
