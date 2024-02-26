#include "Vulkan.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace prf::gui{

//Constructor / Destructor
Vulkan::Vulkan(prf::Node* node_profiler){
  //---------------------------


  //---------------------------
}
Vulkan::~Vulkan(){}

//Main function
void Vulkan::draw_graph(prf::vulkan::Manager* prf_vulkan){
  ImVec2 graph_dim = ImGui::GetContentRegionAvail();
  //---------------------------

  ImGui::SetNextItemWidth(100);
  if (ImGui::BeginTabItem("Vulkan##4567", NULL)){
    this->draw_profiler(prf_vulkan, graph_dim);
    ImGui::EndTabItem();
  }

  //---------------------------
}

//Profiler graphs
void Vulkan::draw_profiler(prf::vulkan::Manager* prf_vulkan, ImVec2 graph_dim){
  vector<prf::vulkan::Device>& vec_device = prf_vulkan->get_info_device();
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  if(ImGui::BeginTabBar("vulkan_profiler_tab##4567")){
    for(int i=0; i< vec_device.size(); i++){
      prf::vulkan::Device& device = vec_device[i];

      if(ImGui::BeginTabItem(device.name.c_str(), NULL)){

        if(ImGui::BeginTable("vulkan_device##profiler", 2)){
          ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthStretch, 75.0f);

          //GPU name
          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("Name"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%s", device.name.c_str());

          //Vendor ID
          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("Vendor ID"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.vendorID);

          //Extension support
          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("Extension support"); ImGui::TableNextColumn();
          const char* support = device.has_extension_support ? "true" : "false";
          ImGui::TextColored(color, "%s", support);

          //Max image
          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("Max image"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.max_image_dim);

          //Queue stuff
          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("Queue graphics ID"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.queue_family_graphics_idx);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("Queue transfer ID"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.queue_family_transfer_idx);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("Queue presentation ID"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.queue_family_presentation_idx);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("No family queues"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.nb_queue_family);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("No graphics queues"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.nb_queue_graphics);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("No compute queues"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.nb_queue_compute);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("No transfer queues"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.nb_queue_transfer);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("No sparse binding queues"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.nb_queue_sparseBinding);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("No presentation queues"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.nb_queue_presentation);

          ImGui::EndTable();
        }

        ImGui::EndTabItem();
      }

    }
    ImGui::EndTabBar();
  }

  //---------------------------
}

}
