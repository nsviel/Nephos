#include "Recorder.h"

#include <Engine/Capture/K4N/Device/Swarm.h>


namespace gui::kinect{

//Constructor / Destructor
Recorder::Recorder(k4n::Node* node_kinect){
  //---------------------------

  this->node_kinect = node_kinect;
  this->k4a_swarm = node_kinect->get_k4a_swarm();

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::kinect_recorder(){
  //---------------------------

  if(ImGui::TreeNode("Recorder")){
    this->recorder_path();

    ImGui::Separator();
    ImGui::TreePop();
  }

  //---------------------------
}

//Subfunction
void Recorder::recorder_path(){
  k4n::Device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  if(ImGui::BeginTable("playback_table##general", 2)){
    //Folder
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Folder"); ImGui::TableNextColumn();
    if(ImGui::Button("...##folder_path")){

    }
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%s", k4a_device->recorder.folder.c_str());

    //File
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("File"); ImGui::TableNextColumn();
    if(ImGui::Button("...##file_path")){

    }
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%s", k4a_device->recorder.path.c_str());

    ImGui::EndTable();
  }

  //---------------------------
}

}
