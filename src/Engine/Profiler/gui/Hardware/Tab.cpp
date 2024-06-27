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

  //Draw specific info
  if(ImGui::BeginTabBar("Hardware##profiler_vulkan")){
    ImVec2 dimension = ImGui::GetContentRegionAvail();

    //GPU tab
    ImGui::SetNextItemWidth(100);
    if(ImGui::BeginTabItem("GPU##profiler_vulkan", NULL)){
      gui_gpu->draw_tab(dimension);
      ImGui::EndTabItem();
    }

    //Device tab
    ImGui::SetNextItemWidth(100);
    if(ImGui::BeginTabItem("Devices##profiler_vulkan", NULL)){
      gui_device->draw_tab(dimension);
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}

//Subfunction

}
