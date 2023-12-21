#include "Operation.h"

#include <Node/GUI.h>
#include <Engine/Capture/K4A/Device/K4A_swarm.h>


namespace gui::kinect{

//Constructor / Destructor
Operation::Operation(eng::kinect::Kinect* kinect){
  //---------------------------

  this->kinect = kinect;
  this->k4a_swarm = kinect->get_k4a_swarm();

  this->item_width = 100;

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::kinect_operation(){
  //---------------------------

  if(ImGui::TreeNode("Operation")){
    this->colorization();

    ImGui::Separator();
    ImGui::TreePop();
  }

  //---------------------------
}

//Subfunction
void Operation::colorization(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  static int color_mode = 2;
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Colorization");
  ImGui::RadioButton("Camera", &k4a_device->cloud.color_mode, 0);
  ImGui::RadioButton("Unicolor", &k4a_device->cloud.color_mode, 1);
  ImGui::RadioButton("White", &k4a_device->cloud.color_mode, 2);
  ImGui::RadioButton("Heatmap", &k4a_device->cloud.color_mode, 3);

  //---------------------------
}

}
