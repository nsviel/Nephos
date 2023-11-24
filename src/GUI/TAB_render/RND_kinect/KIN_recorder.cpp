#include "KIN_recorder.h"

#include <UTL_capture/UTL_kinect/Kinect.h>


//Constructor / Destructor
KIN_recorder::KIN_recorder(Kinect* kinect){
  //---------------------------

  this->kinect = kinect;

  //---------------------------
}
KIN_recorder::~KIN_recorder(){}

//Main function
void KIN_recorder::kinect_recorder(){
  K4A_device* device = kinect->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  if(ImGui::Button("Record")){
    //k4a_recorder->record_mkv(device);
  }

  //---------------------------
}

//Subfunction
