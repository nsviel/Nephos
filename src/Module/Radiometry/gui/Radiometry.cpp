#include "Radiometry.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::gui{

//Constructor / Destructor
Radiometry::Radiometry(rad::Node* node_radio, bool* show_window){
  //---------------------------

  //this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->radio_struct = node_radio->get_radio_struct();
  this->gui_detection = new rad::gui::Detection(node_radio);
  this->gui_calibration = new rad::gui::Calibration(node_radio);

  this->show_window = show_window;
  this->name = "Radiometry";

  //---------------------------
}
Radiometry::~Radiometry(){}

//Main function
void Radiometry::run_panel(){
/*  k4n::dev::Master* master = k4n_swarm->get_selected_master();
  //---------------------------

  if(*show_window && master != nullptr){
    radio_struct->panel_open = true;

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(100, 400), ImVec2(FLT_MAX, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel(master);

      ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
  }else{
    radio_struct->panel_open = false;
  }
*/
  //---------------------------
}
void Radiometry::design_panel(k4n::dev::Master* master){
  k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(master->active_entity);
  //---------------------------

  this->matching_parameter(sensor);

  ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(39, 74, 90, 255));
  ImGui::PushStyleColor(ImGuiCol_TabHovered, IM_COL32(54, 112, 131, 255));
  ImGui::PushStyleColor(ImGuiCol_TabActive, IM_COL32(44, 101, 131, 255));
  ImGui::BeginTabBar("devices_tab##4567");

  this->tab_detection(sensor);
  this->tab_calibration(sensor);

  ImGui::EndTabBar();
  ImGui::PopStyleColor(3);

  //---------------------------
}

//Subfunction
void Radiometry::matching_parameter(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Model parameter");

  //Radiometry sphere radius
  ImGui::SetNextItemWidth(150);
  ImGui::SliderFloat("Sphere diameter", &sensor->detection.sphere_diameter, 0.001, 0.5f, "%.3f m");

  gui_calibration->draw_calibration_player(sensor);

  //---------------------------
  ImGui::Separator();
}
void Radiometry::tab_detection(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x/3-3.33);
  if(ImGui::BeginTabItem("Detection##matching")){
    gui_detection->draw_detection(sensor);

    ImGui::EndTabItem();
  }

  //---------------------------
}
void Radiometry::tab_calibration(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x/3-3.33);
  if(ImGui::BeginTabItem("Calibration##matching")){
    gui_calibration->draw_calibration_tab(sensor);

    ImGui::EndTabItem();
  }

  //---------------------------
}


}
