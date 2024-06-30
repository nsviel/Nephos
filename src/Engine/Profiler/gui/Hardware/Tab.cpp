#include "Tab.h"

#include <Profiler/Namespace.h>


namespace prf::gui::hardware{

//Constructor / Destructor
Tab::Tab(prf::Node* node_profiler){
  //---------------------------

  this->gui_gpu = new prf::gui::hardware::GPU(node_profiler);
  this->gui_cpu = new prf::gui::hardware::CPU(node_profiler);
  this->gui_device = new prf::gui::hardware::Device(node_profiler);

  //---------------------------
}
Tab::~Tab(){}

//Main function
void Tab::draw_tab(int width){
  //---------------------------

  ImGui::SetNextItemWidth(width);
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
    int width = ImGui::GetContentRegionAvail().x;

    //GPU tab
    ImGui::SetNextItemWidth(width / 3.0f);
    if(ImGui::BeginTabItem("GPU##tabitem", NULL)){
      gui_gpu->draw_tab();
      ImGui::EndTabItem();
    }

    //CPU tab
    ImGui::SetNextItemWidth(width / 3.0f);
    if(ImGui::BeginTabItem("CPU##tabitem", NULL)){
      gui_cpu->draw_tab();
      ImGui::EndTabItem();
    }

    //Device tab
    ImGui::SetNextItemWidth(width / 3.0f);
    if(ImGui::BeginTabItem("Devices##tabitem", NULL)){
      gui_device->draw_tab();
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}

}
