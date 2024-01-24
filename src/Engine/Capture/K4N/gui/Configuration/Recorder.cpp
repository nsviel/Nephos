#include "Recorder.h"


namespace eng::k4n::gui{

//Constructor / Destructor
Recorder::Recorder(eng::k4n::Node* k4a_node){
  //---------------------------

  this->k4a_node = k4a_node;
  this->k4n_swarm = k4a_node->get_k4n_swarm();

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
  eng::k4n::dev::Sensor* k4n_sensor = k4n_swarm->get_selected_sensor();
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
