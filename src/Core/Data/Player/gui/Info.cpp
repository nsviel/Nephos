#include "Info.h"

#include <Data/Player/Namespace.h>
#include <Data/Base/Namespace.h>
#include <imgui/core/imgui.h>


namespace dat::ply::gui{

//Constructor / Destructor
Info::Info(){
  //---------------------------



  //---------------------------
}
Info::~Info(){}

//Main function
void Info::design_info(std::shared_ptr<utl::base::Element> element){
  //---------------------------

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Info##dynamic")){
    this->path_info(element);
    this->sensor_info(element);
  }

  //---------------------------
}
void Info::design_configuration(std::shared_ptr<utl::base::Element> element){
  std::shared_ptr<dat::base::Sensor> sensor = std::dynamic_pointer_cast<dat::base::Sensor>(element);
  if(!sensor) return;
  //---------------------------

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Configuration##dynamic")){
    sensor->gui_config();
  }

  //---------------------------
}

//Subfunction
void Info::path_info(std::shared_ptr<utl::base::Element> element){
  std::shared_ptr<dat::base::Entity> entity = std::dynamic_pointer_cast<dat::base::Entity>(element);
  if(!entity) return;
  //---------------------------

  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  utl::base::Data& data = *entity->data;
  utl::base::Pose& pose = *entity->pose;

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Path");
  ImGui::BeginTable("sensor##info", 2);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 75.0f);
  ImGui::TableSetupColumn("2", ImGuiTableColumnFlags_WidthStretch);

  //Data
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Data"); ImGui::TableNextColumn();
  std::string path_data = data.path.directory + data.path.name + data.path.format;
  if(path_data == "") path_data = "(not defined)";
  ImGui::TextColored(color, "%s", path_data.c_str());

  //Transformation
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Transform"); ImGui::TableNextColumn();
  std::string path_transfo = pose.path.directory + pose.path.name + pose.path.format;
  if(path_transfo == "") path_transfo = "(not defined)";
  ImGui::TextColored(color, "%s", path_transfo.c_str());

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Info::sensor_info(std::shared_ptr<utl::base::Element> element){
  std::shared_ptr<dat::base::Sensor> sensor = std::dynamic_pointer_cast<dat::base::Sensor>(element);
  if(!sensor) return;
  //---------------------------

  sensor->gui_info();

  //---------------------------
  ImGui::Separator();
}

}
