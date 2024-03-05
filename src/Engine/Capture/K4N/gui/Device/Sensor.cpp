#include "Sensor.h"

#include <K4N/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n){
  //---------------------------

  this->node_k4n = node_k4n;
  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->k4n_transfo = new k4n::utils::Transformation();

  this->item_width = 100;

  //---------------------------
}
Sensor::~Sensor(){}

//Main function
void Sensor::show_sensor(k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  //---------------------------

  this->show_sensor_info(sensor);
  this->show_sensor_transfo(sensor);
  this->show_firmware_info(sensor);

  //---------------------------
}

//Subfunction
void Sensor::show_sensor_info(k4n::dev::Sensor* sensor){
  //---------------------------

  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  if(ImGui::BeginTable("Kinect_info##general", 2)){
    //Type
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Type"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->entity_type.c_str());

    //File path
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Path data"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->param.path.data.c_str());

    //File size
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Size"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.2f Mo", sensor->param.file_size);

    //Transformation matrix file path
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Path transfo"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->param.path.transformation.c_str());

    ImGui::EndTable();
  }

  //---------------------------
}
void Sensor::show_sensor_transfo(k4n::dev::Sensor* sensor){
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
  ImGui::Separator();
}
void Sensor::show_firmware_info(k4n::dev::Sensor* sensor){
  //---------------------------

  if (ImGui::TreeNode("Device Firmware Version Info")){
    k4a_hardware_version_t versionInfo = sensor->param.version;
    ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
    if(ImGui::BeginTable("device##firmware", 2)){
      ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("RGB camera"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%u.%u.%u", versionInfo.rgb.major, versionInfo.rgb.minor, versionInfo.rgb.iteration);

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Depth camera"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%u.%u.%u", versionInfo.depth.major, versionInfo.depth.minor, versionInfo.depth.iteration);

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Audio"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%u.%u.%u", versionInfo.audio.major, versionInfo.audio.minor, versionInfo.audio.iteration);

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Build config"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%s", versionInfo.firmware_build == K4A_FIRMWARE_BUILD_RELEASE ? "Release" : "Debug");

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Signature type"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%s", versionInfo.firmware_signature == K4A_FIRMWARE_SIGNATURE_MSFT ? "Microsoft" : versionInfo.firmware_signature == K4A_FIRMWARE_SIGNATURE_TEST ? "Test" : "Unsigned");

      ImGui::EndTable();
    }

    ImGui::TreePop();
  }

  //---------------------------
}

}
