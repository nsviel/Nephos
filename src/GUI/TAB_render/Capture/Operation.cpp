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
    ImGui::Unindent();
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

  //Colorization mode
  static int color_mode = 2;
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Colorization");
  ImGui::RadioButton("RGB##colorization", &k4a_device->cloud.color_mode, 0);
  ImGui::SameLine();
  ImGui::RadioButton("##unicolor", &k4a_device->cloud.color_mode, 1);
  ImGui::SameLine();
  ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar;
  ImGui::ColorEdit4("##unicolor_choice", (float*)&k4a_device->cloud.object->unicolor, flags);
  ImGui::SameLine();
  ImGui::RadioButton("I##colorization", &k4a_device->cloud.color_mode, 2);
  ImGui::SameLine();
  ImGui::RadioButton("Heatmap##colorization", &k4a_device->cloud.color_mode, 3);

  //Intensity cursor
  if(k4a_device->cloud.color_mode == 2){
    ImGui::SetNextItemWidth(100);
    ImGui::SliderInt("Intensity division", &k4a_device->cloud.intensity_division, 1, 5000);
  }

  //Heatmap mode
  if(k4a_device->cloud.color_mode == 3){
    ImGui::Indent();
    ImGui::RadioButton("I##heatmap", &k4a_device->cloud.heatmap_mode, 0);
    ImGui::SameLine();
    ImGui::RadioButton("H##heatmap", &k4a_device->cloud.heatmap_mode, 1);
    ImGui::SameLine();
    ImGui::RadioButton("R##heatmap", &k4a_device->cloud.heatmap_mode, 2);

    if(k4a_device->cloud.heatmap_mode == 0){
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Intensity division", &k4a_device->cloud.intensity_division, 1, 5000);
    }
    ImGui::Unindent();
  }

  //---------------------------
}

}
