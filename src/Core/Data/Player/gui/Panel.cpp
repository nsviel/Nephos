#include "Panel.h"

#include <Data/Player/Namespace.h>
#include <Data/Graph/Namespace.h>
#include <Data/Attribut/Namespace.h>
#include <Engine/Transformation/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>
#include <imgui/core/imgui.h>


namespace dat::ply::gui{

//Constructor / Destructor
Panel::Panel(dat::ply::Node* node_player, bool* show_window){
  //---------------------------

  dat::atr::Node* node_attribut = node_player->get_node_attribut();
  dat::gph::Node* node_graph = node_player->get_node_graph();

  this->gph_selection = node_graph->get_gph_selection();
  this->gui_info = new dat::ply::gui::Info();
  this->gui_player = new dat::ply::gui::Player(node_player);
  this->gui_transformation = new eng::trf::gui::Matrix();
  this->gui_color = new dat::atr::gui::Color(node_attribut);

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
  std::shared_ptr<utl::base::Element> element = gph_selection->get_selected_element();
  std::shared_ptr<dat::base::Set> set = gph_selection->get_selected_set();
  if(!element || !set) return;
  //---------------------------

  gui_player->design_player(*set);
  gui_info->design_info(element);
  gui_info->design_configuration(element);
  gui_color->design_header(element);
  gui_transformation->design_matrix(element);

  //---------------------------
  ImGui::Separator();
}

}
