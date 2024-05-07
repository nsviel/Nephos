#include "Sensor.h"

#include <Kinect/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n){
  //---------------------------

  this->node_k4n = node_k4n;
  this->k4n_transfo = new k4n::utils::Transformation();
  this->gui_playback = new k4n::gui::Playback(node_k4n);

  this->item_width = 100;

  //---------------------------
}
Sensor::~Sensor(){}

//Main function
void Sensor::show_sensor(k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  //---------------------------

  this->show_sensor_info(sensor);

  ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(39, 74, 90, 255));
  ImGui::PushStyleColor(ImGuiCol_TabHovered, IM_COL32(54, 112, 131, 255));
  ImGui::PushStyleColor(ImGuiCol_TabActive, IM_COL32(44, 101, 131, 255));
  if(ImGui::BeginTabBar("master_option##tab")){
    this->show_sensor_transfo(sensor);

    ImGui::SetNextItemWidth(75);
    if(ImGui::BeginTabItem("Info##3443", NULL)){
      this->show_firmware_info(sensor);
      gui_playback->show_sensor_configuration(sensor);

      ImGui::EndTabBar();
    }

    ImGui::EndTabBar();
  }
  ImGui::PopStyleColor(3);

  this->show_sensor_recorder(sensor);

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
    string path_data = (sensor->param.path.data != "") ? sensor->param.path.data : "(not defined)";
    ImGui::TextColored(color, "%s", path_data.c_str());

    //Transformation matrix file path
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Path transfo"); ImGui::TableNextColumn();
    string path_transfo = (sensor->param.path.transformation != "") ? sensor->param.path.transformation : "(not defined)";
    ImGui::TextColored(color, "%s", path_transfo.c_str());

    //File size
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Size"); ImGui::TableNextColumn();

    ImGui::TextColored(color, "%.2f Mo", sensor->param.file_size);

    ImGui::EndTable();
  }

  //---------------------------
}
void Sensor::show_sensor_transfo(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::SetNextItemWidth(75);
  if(ImGui::BeginTabItem("Matrix##3443", NULL)){
    //Object model matrix
    dat::base::Object* object = sensor->get_object();
    mat4& model = object->pose.model;
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

    ImGui::EndTabItem();
  }

  //---------------------------
  ImGui::Separator();
}
void Sensor::show_firmware_info(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Device Firmware Version Info");

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

  //---------------------------
  ImGui::Separator();
}
void Sensor::show_sensor_recorder(k4n::dev::Sensor* sensor){
  //---------------------------

  if(ImGui::TreeNode("Recorder")){
    this->recorder_path(sensor);

    ImGui::Separator();
    ImGui::TreePop();
  }

  //---------------------------
}
void Sensor::recorder_path(k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  //---------------------------

  if(ImGui::BeginTable("playback_table##general", 2)){
    //Folder
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Folder"); ImGui::TableNextColumn();
    if(ImGui::Button("...##folder_path")){

    }
    ImGui::SameLine();
    if(ImGui::Button(ICON_FA_FOLDER "##file_path")){
      utl::directory::open(sensor->master->recorder.folder);
    }
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%s", sensor->master->recorder.folder.c_str());

    //File
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("File"); ImGui::TableNextColumn();
    if(ImGui::Button("...##file_path")){

    }
    ImGui::SameLine();
    if(ImGui::Button(ICON_FA_FOLDER "##file_path")){
      utl::directory::open(sensor->master->recorder.filename);
    }
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%s", sensor->master->recorder.filename.c_str());

    ImGui::EndTable();
  }

  //---------------------------
}

}
