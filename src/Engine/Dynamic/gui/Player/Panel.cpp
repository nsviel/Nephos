#include "Panel.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dyn::gui::player{

//Constructor / Destructor
Panel::Panel(dyn::Node* node_dynamic, bool* show_window){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();

  this->dat_selection = node_data->get_dat_selection();
  this->gui_colorization = new ope::gui::Colorization(node_dynamic);
  this->gui_transformation = new ope::gui::Transformation(node_dynamic);
  this->gui_information = new ope::gui::Info(node_dynamic);
  this->gui_configuration = new ope::gui::Configuration(node_dynamic);
  this->gui_normal = new ope::gui::Normal(node_dynamic);
  this->gui_player = new dyn::gui::Player(node_dynamic);

  this->show_window = show_window;
  this->name = "Player";

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  //---------------------------

  if(*show_window){
    ImGuiWindowFlags flag;
    flag |= ImGuiWindowFlags_NoCollapse;
    flag |= ImGuiWindowFlags_AlwaysAutoResize;
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(250, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, flag) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(){
  utl::base::Element* element = dat_selection->get_selected_element();
  if(element == nullptr) return;
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));

  gui_player->design_player(element);
  gui_information->design_info(element);
  gui_configuration->design_configuration(element);
  gui_transformation->design_transformation(element);
  gui_colorization->design_colorization(element);
  gui_normal->design_normal();

  ImGui::PopStyleColor();

  //---------------------------
  ImGui::Separator();
}

}
