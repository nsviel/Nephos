#include "Panel.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::gui{

//Constructor / Destructor
Panel::Panel(rad::Node* node_radio, bool* show_window){
  //---------------------------

  dat::Node* node_data = node_radio->get_node_data();

  this->dat_graph = node_data->get_data_graph();
  this->radio_struct = node_radio->get_radio_struct();
  this->gui_detection = new rad::gui::Detection(node_radio);
  this->gui_calibration = new rad::gui::Calibration(node_radio);

  this->show_window = show_window;
  this->name = "Radiometry";

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  utl::type::Element* element = dat_graph->get_selection();
  //---------------------------

  //Convert it into proper format
  dat::base::Entity* entity;
  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    entity = set->active_entity;
  }else{
    entity = dynamic_cast<dat::base::Entity*>(element);
  }

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(100, 400), ImVec2(FLT_MAX, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel(entity);

      ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(dat::base::Entity* entity){
  //---------------------------

  this->matching_parameter(entity);

  ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(39, 74, 90, 255));
  ImGui::PushStyleColor(ImGuiCol_TabHovered, IM_COL32(54, 112, 131, 255));
  ImGui::PushStyleColor(ImGuiCol_TabActive, IM_COL32(44, 101, 131, 255));
  ImGui::BeginTabBar("devices_tab##4567");

  this->tab_detection(entity);
  this->tab_calibration(entity);

  ImGui::EndTabBar();
  ImGui::PopStyleColor(3);

  //---------------------------
}

//Subfunction
void Panel::matching_parameter(dat::base::Entity* entity){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Model parameter");

  //Radiometry sphere radius
  ImGui::SetNextItemWidth(150);
  ImGui::SliderFloat("Sphere diameter", &radio_struct->detection.sphere_diameter, 0.001, 0.5f, "%.3f m");

  gui_calibration->draw_calibration_player();

  //---------------------------
  ImGui::Separator();
}
void Panel::tab_detection(dat::base::Entity* entity){
  //---------------------------

  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x/3-3.33);
  if(ImGui::BeginTabItem("Detection##matching")){
    gui_detection->draw_detection();

    ImGui::EndTabItem();
  }

  //---------------------------
}
void Panel::tab_calibration(dat::base::Entity* entity){
  //---------------------------

  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x/3-3.33);
  if(ImGui::BeginTabItem("Calibration##matching")){
    gui_calibration->draw_calibration_tab();

    ImGui::EndTabItem();
  }

  //---------------------------
}


}
