#include "Tab.h"

#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace prf::gui::hardware{

//Constructor / Destructor
Tab::Tab(prf::Node* node_profiler){
  //---------------------------

  this->gui_gpu = new prf::gui::hardware::GPU(node_profiler);
  this->gui_device = new prf::gui::hardware::Device(node_profiler);

  //---------------------------
}
Tab::~Tab(){}

//Main function
void Tab::draw_tab(){
  //---------------------------

  if(ImGui::BeginTabItem("Hardware")){
    this->draw_hardware_tabbar();

    ImGui::EndTabItem();
  }

  //---------------------------
}

//Subfunction
void Tab::draw_hardware_tabbar(){
  //---------------------------

  //Draw specific info
  if(ImGui::BeginTabBar("Hardware##tabbar")){
    ImVec2 dimension = ImGui::GetContentRegionAvail();

    //GPU tab
    ImGui::SetNextItemWidth(100);
    if(ImGui::BeginTabItem("GPU##tabitem", NULL)){
      gui_gpu->draw_tab(dimension);
      ImGui::EndTabItem();
    }

    //Device tab
    ImGui::SetNextItemWidth(100);
    if(ImGui::BeginTabItem("Devices##tabitem", NULL)){
      gui_device->draw_tab(dimension);
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}

}
