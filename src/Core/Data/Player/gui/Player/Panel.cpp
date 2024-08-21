#include "Panel.h"

#include <Data/Player/Namespace.h>
#include <Data/Graph/Namespace.h>
#include <Data/Attribut/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat::ply::gui{

//Constructor / Destructor
Panel::Panel(dat::ply::Node* node_player, bool* show_window){
  //---------------------------

  dat::atr::Node* node_attribut = node_player->get_node_attribut();
  dat::gph::Node* node_graph = node_player->get_node_graph();

  this->dat_selection = node_graph->get_gph_selection();
  this->gui_configuration = new dat::ply::gui::Configuration();
  this->gui_player = new dat::ply::gui::Player(node_player);
  this->atr_panel = node_attribut->get_gui_panel();

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
  gui_configuration->design_configuration(element);
  atr_panel->design_panel(element);

  ImGui::PopStyleColor();

  //---------------------------
  ImGui::Separator();
}

}
