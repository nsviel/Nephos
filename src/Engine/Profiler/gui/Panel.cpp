#include "Panel.h"

#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace prf::gui{

//Constructor / Destructor
Panel::Panel(prf::Node* node_profiler, bool* show_window){
  //---------------------------

  this->prf_manager = node_profiler->get_prf_manager();
  this->tab_dynamic = new prf::gui::dynamic::Tab(node_profiler);
  this->tab_hardware = new prf::gui::hardware::Tab(node_profiler);

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
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){
      this->design_panel();
      ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(){
  int width = ImGui::GetContentRegionAvail().x / list_profiler.size() + 1;
  //---------------------------

  if(ImGui::BeginTabBar("profiler_panel##graph")){
    tab_hardware->draw_tab(width);
    tab_hardware->draw_tab(width);

    ImGui::EndTabBar();
  }
  //---------------------------
}

//Subfunction

}
