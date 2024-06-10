#include "Panel.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Data/Namespace.h>


namespace rad::gui{

//Constructor / Destructor
Panel::Panel(rad::Node* node_radio, bool* show_window){
  //---------------------------

  dat::Node* node_data = node_radio->get_node_data();

  this->dat_selection = node_data->get_dat_selection();
  this->gui_detection = new rad::gui::Detection(node_radio);
  this->gui_model = new rad::gui::Model(node_radio);
  this->gui_correction = new rad::gui::Correction(node_radio);

  this->show_window = show_window;
  this->name = "Radiometry";

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(600, 600));
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

  ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(39, 74, 90, 255));
  ImGui::PushStyleColor(ImGuiCol_TabHovered, IM_COL32(54, 112, 131, 255));
  ImGui::PushStyleColor(ImGuiCol_TabActive, IM_COL32(44, 101, 131, 255));
  ImGui::BeginTabBar("devices_tab##4567");

  this->tab_detection(entity);
  this->tab_modeld(entity);
  this->tab_calibration(entity);

  ImGui::EndTabBar();
  ImGui::PopStyleColor(3);

  //---------------------------
}

//Subfunction
void Panel::tab_detection(dat::base::Entity* entity){
  //---------------------------

  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x/3-3.33);
  if(ImGui::BeginTabItem("Detection##matching")){
    gui_detection->draw_tab();

    ImGui::EndTabItem();
  }

  //---------------------------
}
void Panel::tab_modeld(dat::base::Entity* entity){
  //---------------------------

  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x/3-3.33);
  if(ImGui::BeginTabItem("Model##matching")){
    gui_model->draw_tab();

    ImGui::EndTabItem();
  }

  //---------------------------
}
void Panel::tab_calibration(dat::base::Entity* entity){
  //---------------------------

  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x/3-3.33);
  if(ImGui::BeginTabItem("Correction##matching")){
    gui_correction->draw_tab();

    ImGui::EndTabItem();
  }

  //---------------------------
}


}
