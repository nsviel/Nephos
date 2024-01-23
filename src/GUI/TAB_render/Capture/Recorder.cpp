#include "Recorder.h"


namespace gui::kinect{

//Constructor / Destructor
Recorder::Recorder(k4n::Node* node_kinect){
  //---------------------------

  this->node_kinect = node_kinect;
  this->k4n_swarm = node_kinect->get_k4n_swarm();

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::show_sensor_recorder(){
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
  k4n::dev::Sensor* k4n_sensor = k4n_swarm->get_selected_sensor();
  if(k4n_sensor == nullptr) return;
  //---------------------------

  if(ImGui::BeginTable("playback_table##general", 2)){
    //Folder
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Folder"); ImGui::TableNextColumn();
    if(ImGui::Button("...##folder_path")){

    }
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%s", k4n_sensor->recorder.folder.c_str());

    //File
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("File"); ImGui::TableNextColumn();
    if(ImGui::Button("...##file_path")){

    }
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%s", k4n_sensor->recorder.path.c_str());

    ImGui::EndTable();
  }

  //---------------------------
}

}
