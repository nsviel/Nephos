#include "Panel.h"

#include <Player/Namespace.h>
#include <Data/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat::ply::gui{

//Constructor / Destructor
Panel::Panel(dat::ply::Node* node_player, bool* show_window){
  //---------------------------
sayHello();
  dat::Node* node_data = node_player->get_node_data();
  ope::Node* node_operation = node_player->get_node_operation();
  dat::gph::Node* node_graph = node_data->get_node_graph();
sayHello();
  this->dat_selection = node_graph->get_dat_selection();sayHello();
  this->gui_configuration = new dat::ply::gui::Configuration();sayHello();
  this->gui_player = new dat::ply::gui::Player(node_player);sayHello();
  this->ope_panel = node_operation->get_gui_panel();sayHello();

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
  ope_panel->design_panel(element);

  ImGui::PopStyleColor();

  //---------------------------
  ImGui::Separator();
}

}
