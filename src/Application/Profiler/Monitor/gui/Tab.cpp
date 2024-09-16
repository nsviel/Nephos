#include "Tab.h"

#include <Monitor/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>


namespace prf::gui::dynamic{

//Constructor / Destructor
Tab::Tab(prf::monitor::Node* node_monitor){
  //---------------------------

  this->prf_struct = node_monitor->get_prf_struct();
  this->gui_graph = new prf::gui::dynamic::Graph(node_monitor);

  //---------------------------
}
Tab::~Tab(){}

//Main function
void Tab::draw_tab(int width){
  //---------------------------

  ImGui::SetNextItemWidth(width);
  if(ImGui::BeginTabItem("Dynamic")){
    this->draw_dynamic_tabbar();

    ImGui::EndTabItem();
  }

  //---------------------------
}

//Subfunction
void Tab::draw_dynamic_tabbar(){
  std::list<prf::monitor::Profiler*>& list_profiler = prf_struct->list_profiler;
  int width = ImGui::GetContentRegionAvail().x / list_profiler.size();
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Tab, utl::colormap::H3_TAB);
  ImGui::PushStyleColor(ImGuiCol_TabHovered, utl::colormap::H3_TAB_HOVERED);
  ImGui::PushStyleColor(ImGuiCol_TabActive, utl::colormap::H3_TAB_ACTIVE);
  if(ImGui::BeginTabBar("profiler_panel##graph")){
    for(auto& profiler : list_profiler){
      ImGui::SetNextItemWidth(width);
      if(ImGui::BeginTabItem(profiler->name.c_str())){
        gui_graph->draw_profiler(profiler);
        ImGui::EndTabItem();
      }
    }

    ImGui::EndTabBar();
  }
  ImGui::PopStyleColor(3);

  //---------------------------
}

}
