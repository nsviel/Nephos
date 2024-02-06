#include "Sensor.h"

#include <Engine/Capture/K4N/Namespace.h>


namespace eng::k4n::gui{

//Constructor / Destructor
Sensor::Sensor(eng::k4n::Node* node_k4n){
  //---------------------------

  this->node_k4n = node_k4n;
  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->k4n_transfo = new eng::k4n::utils::Transformation();

  this->item_width = 100;

  //---------------------------
}
Sensor::~Sensor(){}

//Main function
void Sensor::show_sensor(eng::k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  //---------------------------

  this->show_sensor_info(sensor);
  this->show_sensor_transfo(sensor);

  //---------------------------
}

//Subfunction
void Sensor::show_sensor_info(eng::k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::Separator();
  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  if(ImGui::BeginTable("Kinect_info##general", 2)){
    //Type
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Type"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->type.c_str());

    //Transformation matrix file path
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Matrix"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->param.path_transfo.c_str());

    ImGui::EndTable();
  }

  //---------------------------
}
void Sensor::show_sensor_transfo(eng::k4n::dev::Sensor* sensor){
  //---------------------------

  //Object model matrix
  utl::entity::Object* object = sensor->get_object();
  mat4& model = object->pose->model;
  ImGui::Columns(4, "ModelMat");
  for(int i=0; i<4; i++){
    ImGui::Separator();
    for(int j=0;j<4;j++){
      ImGui::Text("%.3f", model[i][j]);
      ImGui::NextColumn();
    }
  }
  ImGui::Separator();
  ImGui::Columns(1);

  ImVec2 width = ImGui::GetContentRegionAvail();
  if(ImGui::Button("Save##transfomatrix", ImVec2(width.x, 0))){
    k4n_transfo->save_transformation_to_file(sensor);
  }
  if(ImGui::Button("Identity##transfomatrix", ImVec2(width.x, 0))){
    k4n_transfo->make_transformation_identity(sensor);
  }

  //---------------------------
}

}
