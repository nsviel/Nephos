#include "Detection.h"

#include <Utility/Namespace.h>
#include <Engine/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Data/Namespace.h>


namespace rad::gui::calibration{

//Constructor / Destructor
Detection::Detection(rad::Node* node_radio){
  //---------------------------

  dat::Node* node_data = node_radio->get_node_data();
  eng::Node* node_engine = node_radio->get_node_engine();
  rad::calibration::Node* node_calibration = node_radio->get_node_calibration();

  this->rad_struct = node_calibration->get_rad_struct();
  this->rad_process = node_calibration->get_rad_process();
  this->stream = new rnd::Stream(node_engine);
  this->dat_image = node_data->get_dat_image();

  //---------------------------
}
Detection::~Detection(){}

//Main function
void Detection::draw_tab(dyn::base::Sensor* sensor){
  //---------------------------

  this->detection_step();
  this->detection_image(sensor);

  //---------------------------
}

//Subfunction
void Detection::detection_step(){
  //---------------------------

  ImGui::BeginTable("detection_step##table", 3);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 100.0f);
  ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthFixed, 15.0f);
  ImGui::TableSetupColumn("three", ImGuiTableColumnFlags_WidthStretch);

  //Detection step
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Detection");
  ImGui::TableNextColumn();
  if(rad_struct->state.detection == rad::calibration::detection::PROCESSING){
    ImGui::Spinner_cicle(ImVec4(1, 1, 1, 1));
  }
  ImGui::TableNextColumn();
  if(rad_struct->state.detection == rad::calibration::detection::WAIT_VALIDATION){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
    if(ImGui::Button("Validate##sphere_detection", ImVec2(120, 0))){
      rad_process->step_detection();
    }
    ImGui::PopStyleColor(2);
  }else if(rad_struct->state.detection == rad::calibration::detection::PROCESSING){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 45, 45, 255));
    if(ImGui::Button("Stop##sphere_detection", ImVec2(120, 0))){
      rad_process->step_detection();
    }
    ImGui::PopStyleColor(2);
  }

  //Measure step
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Measure");
  ImGui::TableNextColumn();
  if(rad_struct->state.measure == rad::calibration::measure::PROCESSING){
    ImGui::Spinner_cicle(ImVec4(1, 1, 1, 1));
  }else{
    switch(rad_struct->state.data){
      case rad::calibration::NO_DATA:{
        ImGui::Cross(ImVec4(1, 0.4, 0.4, 1));
        break;
      }
      case rad::calibration::HAS_DATA:{
        ImGui::Check_on();
        break;
      }
    }
  }
  ImGui::TableNextColumn();
  if(rad_struct->state.measure == rad::calibration::measure::WAIT_VALIDATION){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
    if(ImGui::Button("Validate##sphere_measure", ImVec2(120, 0))){
      rad_process->step_measure();
    }
    ImGui::PopStyleColor(2);
  }else if(rad_struct->state.measure == rad::calibration::measure::PROCESSING){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 45, 45, 255));
    if(ImGui::Button("Stop##sphere_measure", ImVec2(120, 0))){
      rad_process->step_measure();
    }
    ImGui::PopStyleColor(2);
  }

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Detection::detection_image(dyn::base::Sensor* sensor){
  ImVec2 available_space = ImGui::GetContentRegionAvail();
  //---------------------------

  //Display image with detected spheres
  utl::media::Image* image = dat_image->get_image(sensor, utl::media::CORRECTION);
  if(image == nullptr) return;
  stream->draw_stream(image, ImVec2(available_space.x, available_space.y - 5));

  //---------------------------
  ImGui::Separator();
}

}
