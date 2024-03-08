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

  if(ImGui::BeginTabBar("vulkan_device##tab_bar")){
    for(int i=0; i< vec_device.size(); i++){
      prf::vulkan::Device& device = vec_device[i];

      if(ImGui::BeginTabItem(device.name.c_str(), NULL)){
        this->draw_table_info(device);
        this->draw_table_queue_families(device);

        ImGui::EndTabItem();
      }

    }
    ImGui::EndTabBar();
  }

  //---------------------------
}
void Vulkan::draw_table_info(prf::vulkan::Device& device){
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  ImGui::BeginTable("vulkan_device##table", 2);

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

  ImGui::EndTable();

  //---------------------------
}
void Vulkan::draw_table_queue_families(prf::vulkan::Device& device){
  //---------------------------

  int size = device.vec_queue_family.size() + 1;
  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  static ImGuiTableFlags flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_RowBg | ImGuiTableFlags_ContextMenuInBody;
  ImGui::BeginTable("vulkan_thread##table", size, flags);

  //Family index
  ImGui::TableSetupColumn("Family");
  for(int i=0; i<device.vec_queue_family.size(); i++){
    ImGui::TableSetupColumn(std::to_string(i).c_str(), ImGuiTableColumnFlags_WidthFixed, 20.0f);
  }
  ImGui::TableHeadersRow();

  //Graphics queue
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Graphics");
  for(int i=0; i<device.vec_queue_family.size(); i++){
    ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", device.vec_queue_family[i].nb_queue_graphics);
  }

  //Compute queue
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Compute");
  for(int i=0; i<device.vec_queue_family.size(); i++){
    ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", device.vec_queue_family[i].nb_queue_compute);
  }

  //Transfer queue
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Transfer");
  for(int i=0; i<device.vec_queue_family.size(); i++){
    ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", device.vec_queue_family[i].nb_queue_transfer);
  }

  //Sparse binding queue
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Sparse binding");
  for(int i=0; i<device.vec_queue_family.size(); i++){
    ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", device.vec_queue_family[i].nb_queue_sparseBinding);
  }

  //Presentation queue
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Presentation");
  for(int i=0; i<device.vec_queue_family.size(); i++){
    ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", device.vec_queue_family[i].nb_queue_presentation);
  }

  ImGui::EndTable();

  //---------------------------
}

}
