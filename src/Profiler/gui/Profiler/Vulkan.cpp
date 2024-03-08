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
void Vulkan::draw_profiler(prf::vulkan::Profiler* prf_vulkan){
  ImVec2 graph_dim = ImGui::GetContentRegionAvail();
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  if(ImGui::BeginTabBar("Vulkan##profiler_vulkan")){
    //Thread tab
    ImGui::SetNextItemWidth(100);
    if(ImGui::BeginTabItem("Thread##profiler_vulkan", NULL)){
      this->draw_thread(prf_vulkan, graph_dim);
      ImGui::EndTabItem();
    }

    //Device tab
    ImGui::SetNextItemWidth(100);
    if(ImGui::BeginTabItem("Device##profiler_vulkan", NULL)){
      this->draw_device(prf_vulkan, graph_dim);
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}

//Subfunction
void Vulkan::draw_thread(prf::vulkan::Profiler* prf_vulkan, ImVec2 graph_dim){
  vector<prf::vulkan::Thread>& vec_thread = prf_vulkan->get_vec_thread();
  //---------------------------

  ImVec4 green = ImVec4(0.5, 1, 0.5, 1);
  ImVec4 blue = ImVec4(0.5, 0.5, 1, 1);
  if(ImGui::BeginTable("vulkan_thread##table", 2)){

    for(int i=0; i<vec_thread.size(); i++){
      prf::vulkan::Thread& thread = vec_thread[i];

      //Thread name
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Name"); ImGui::TableNextColumn();
      ImGui::TextColored(green, "%s", thread.name.c_str());

      //Thread ID
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("ID"); ImGui::TableNextColumn();
      std::stringstream ss;
      ss << thread.ID;
      ImGui::TextColored(blue, "%s", ss.str().c_str());

      ImGui::Separator();
    }
    ImGui::EndTable();
  }

  //---------------------------
}
void Vulkan::draw_device(prf::vulkan::Profiler* prf_vulkan, ImVec2 graph_dim){
  vector<prf::vulkan::Device>& vec_device = prf_vulkan->get_info_device();
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  if(ImGui::BeginTabBar("vulkan_device##tab_bar")){
    for(int i=0; i< vec_device.size(); i++){
      prf::vulkan::Device& device = vec_device[i];

      if(ImGui::BeginTabItem(device.name.c_str(), NULL)){

        if(ImGui::BeginTable("vulkan_device##table", 2)){
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
          ImGui::TableNextRow();
          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("Queue graphics ID"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.queue_family_graphics_idx);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("Queue transfer ID"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.queue_family_transfer_idx);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("Queue presentation ID"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.queue_family_presentation_idx);

          this->draw_queue_families(device);

          ImGui::EndTable();
        }

        ImGui::EndTabItem();
      }

    }
    ImGui::EndTabBar();
  }

  //---------------------------
}
void Vulkan::draw_queue_families(prf::vulkan::Device& device){
  //---------------------------
  /*
  //Transformer ici en table
  queue       family_0      family_1
  graphics
  presentation
  ...
*/
  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  for(int i=0; i<device.vec_queue_family.size(); i++){
    prf::vulkan::Queue_family& queue_family = device.vec_queue_family[i];

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Queue - graphics"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", queue_family.nb_queue_graphics);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Queue - compute"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", queue_family.nb_queue_compute);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Queue - transfer"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", queue_family.nb_queue_transfer);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Queue - sparse binding"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", queue_family.nb_queue_sparseBinding);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Queue - presentation"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", queue_family.nb_queue_presentation);
  }

  //---------------------------
}

}
