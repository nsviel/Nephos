#include "Tab.h"

#include <Profiler/Namespace.h>


namespace prf::gui::dynamic{

//Constructor / Destructor
Tab::Tab(prf::Node* node_profiler){
  //---------------------------

  this->gui_graph = new prf::gui::dynamic::Graph(node_profiler);

  //---------------------------
}
Tab::~Tab(){}

//Main function
void Tab::draw_tab(){
  //---------------------------

  if(ImGui::BeginTabItem("Hardware")){
    this->draw_dynamic_tabbar();

    ImGui::EndTabItem();
  }

  //---------------------------
}

//Subfunction
void Tab::draw_dynamic_tabbar(){
  //---------------------------

  //Draw specific info
  if(ImGui::BeginTabBar("Hardware##tabbar")){
    int width = ImGui::GetContentRegionAvail().x;


    ImGui::SetNextItemWidth(width / 2.0f);
    if(ImGui::BeginTabItem("GPU##tabitem", NULL)){
      //gui_graph->draw_tab();
      ImGui::EndTabItem();
    }


    ImGui::EndTabBar();
  }

  //---------------------------
}

}
