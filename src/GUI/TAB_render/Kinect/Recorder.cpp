#include "Recorder.h"

#include <Engine/Capture/Kinect/Device/K4A_swarm.h>


namespace gui::kinect{

//Constructor / Destructor
Recorder::Recorder(eng::kinect::Kinect* kinect){
  //---------------------------

  this->kinect = kinect;
  this->k4a_swarm = kinect->get_k4a_swarm();

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::kinect_recorder(){
  K4A_device* device = k4a_swarm->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  if(ImGui::TreeNode("Recorder")){
    if(ImGui::Button("Button")){
    }

    ImGui::TreePop();
  }

  //---------------------------
}

//Subfunction

}
