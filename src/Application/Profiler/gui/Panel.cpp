#include "Panel.h"

#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>


namespace prf::gui{

//Constructor / Destructor
Panel::Panel(prf::Node* node_profiler, bool* show_window){
  //---------------------------

  prf::monitor::Node* node_monitor = node_profiler->get_node_monitor();
  prf::hardware::Node* node_hardware = node_profiler->get_node_hardware();

  this->tab_monitor = new prf::gui::dynamic::Tab(node_monitor);
  this->tab_hardware = new prf::gui::hardware::Tab(node_hardware);

  this->show_window = show_window;
  this->name = "Profiler";
  this->width = 150;

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(600, 600));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_NoResize) == 1){
      this->design_panel();
      ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(){
  int width = ImGui::GetContentRegionAvail().x / 2;
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Tab, utl::colormap::H2_TAB);
  ImGui::PushStyleColor(ImGuiCol_TabHovered, utl::colormap::H2_TAB_HOVERED);
  ImGui::PushStyleColor(ImGuiCol_TabActive, utl::colormap::H2_TAB_ACTIVE);
  if(ImGui::BeginTabBar("profiler_panel##graph")){
    tab_monitor->draw_tab(width);
    tab_hardware->draw_tab(width);

    ImGui::EndTabBar();
  }
  ImGui::PopStyleColor(3);

  //---------------------------
}

//Subfunction

}
