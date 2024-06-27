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
void Tab::show_profiler(prf::base::Profiler* profiler){
  //---------------------------

  //Retrieve vulkan info struct
  prf::hardware::Profiler* prf_vulkan = dynamic_cast<prf::hardware::Profiler*>(profiler);
  if(prf_vulkan == nullptr) return;
  prf::hardware::Structure* prf_struct = prf_vulkan->get_prf_struct();

  //Draw specific info
  if(ImGui::BeginTabBar("Hardware##profiler_vulkan")){
    ImVec2 dimension = ImGui::GetContentRegionAvail();

    //GPU tab
    ImGui::SetNextItemWidth(100);
    if(ImGui::BeginTabItem("GPU##profiler_vulkan", NULL)){
      gui_gpu->draw_tab(prf_struct, dimension);
      ImGui::EndTabItem();
    }

    //Device tab
    ImGui::SetNextItemWidth(100);
    if(ImGui::BeginTabItem("Devices##profiler_vulkan", NULL)){
      gui_device->draw_tab(prf_struct, dimension);
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}

//Subfunction

}
