#include "Panel.h"

#include <Radiometry/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace rad::gui{

//Constructor / Destructor
Panel::Panel(rad::Node* node_radio, bool* show_window){
  //---------------------------

  dat::Node* node_data = node_radio->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();

  this->gph_selection = node_graph->get_gph_selection();
  this->gui_correction = new rad::cor::gui::Tab(node_radio);
  this->gui_calibration = new rad::cal::gui::Tab(node_radio);

  this->show_window = show_window;
  this->name = "Radiometry";

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  std::shared_ptr<dat::base::Entity> entity = gph_selection->get_selected_entity();
  auto sensor = std::dynamic_pointer_cast<dat::base::Sensor>(entity);
  if(!sensor) return;
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(600, 600));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel(*sensor);

      ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(dat::base::Sensor& sensor){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(39, 39, 39, 255));
  ImGui::PushStyleColor(ImGuiCol_TabHovered, IM_COL32(130, 130, 130, 255));
  ImGui::PushStyleColor(ImGuiCol_TabActive, IM_COL32(101, 101, 101, 255));
  ImGui::BeginTabBar("devices_tab##4567");

  this->tab_correction(sensor);
  this->tab_calibration(sensor);

  ImGui::EndTabBar();
  ImGui::PopStyleColor(3);

  //---------------------------
}

//Subfunction
void Panel::tab_correction(dat::base::Sensor& sensor){
  //---------------------------

  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x / 2);
  if(ImGui::BeginTabItem("Correction##radiometry_tab")){
    gui_correction->design_tab(sensor);

    ImGui::EndTabItem();
  }

  //---------------------------
}
void Panel::tab_calibration(dat::base::Sensor& sensor){
  //---------------------------

  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x / 2);
  if(ImGui::BeginTabItem("Calibration##radiometry_tab")){
    gui_calibration->design_tab(sensor);

    ImGui::EndTabItem();
  }

  //---------------------------
}

}
