#include "Recorder.h"

#include <K4N/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Recorder::Recorder(k4n::Node* node_k4n){
  //---------------------------

  this->node_k4n = node_k4n;
  this->k4n_swarm = node_k4n->get_k4n_swarm();

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::show_sensor_recorder(k4n::dev::Sensor* sensor){
  //---------------------------

  if(ImGui::TreeNode("Recorder")){
    this->recorder_path(sensor);

    ImGui::Separator();
    ImGui::TreePop();
  }

  //---------------------------
}

//Subfunction
void Recorder::recorder_path(k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  //---------------------------

  if(ImGui::BeginTable("playback_table##general", 2)){
    //Folder
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Folder"); ImGui::TableNextColumn();
    if(ImGui::Button("...##folder_path")){

    }
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%s", sensor->master->recorder.folder.c_str());

    //File
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("File"); ImGui::TableNextColumn();
    if(ImGui::Button("...##file_path")){

    }
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%s", sensor->master->recorder.filename.c_str());

    ImGui::EndTable();
  }

  //---------------------------
}

}
