#include "Recorder.h"


namespace gui::kinect{

//Constructor / Destructor
Recorder::Recorder(eng::kinect::Kinect* kinect){
  //---------------------------

  this->kinect = kinect;

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::kinect_recorder(){
  K4A_device* device = kinect->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  if(ImGui::Button("Record")){
    //k4a_recorder->record_mkv(device);
  }

  //---------------------------
}

//Subfunction

}
