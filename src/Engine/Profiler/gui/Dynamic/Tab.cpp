#include "Tab.h"

#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>


namespace prf::gui::dynamic{

//Constructor / Destructor
Tab::Tab(prf::Node* node_profiler){
  //---------------------------

  this->prf_manager = node_profiler->get_prf_manager();
  this->gui_graph = new prf::gui::dynamic::Graph(node_profiler);

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
  std::list<prf::dynamic::Profiler*> list_profiler = prf_manager->get_list_profiler();
  int width = ImGui::GetContentRegionAvail().x / list_profiler.size();
  //---------------------------

  if(ImGui::BeginTabBar("profiler_panel##graph")){
    for(int i=0; i<list_profiler.size(); i++){
      prf::dynamic::Profiler* profiler = *next(list_profiler.begin(), i);

      ImGui::SetNextItemWidth(width);
      if(ImGui::BeginTabItem(profiler->name.c_str())){
        gui_graph->draw_profiler(profiler);
        ImGui::EndTabItem();
      }
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}

}
