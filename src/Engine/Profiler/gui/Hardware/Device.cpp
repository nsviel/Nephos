#include "Device.h"

#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace prf::gui::hardware{

//Constructor / Destructor
Device::Device(prf::Node* node_profiler){
  //---------------------------

  this->prf_struct = node_profiler->get_prf_struct();

  //---------------------------
}
Device::~Device(){}

//Main function
void Device::draw_tab(ImVec2 dimension){
  //---------------------------

  if(ImGui::BeginTabBar("vulkan_device##tab_bar")){
    for(int i=0; i<prf_struct->hardware.vec_device.size(); i++){
      prf::hardware::Device& device = prf_struct->hardware.vec_device[i];

      if(ImGui::BeginTabItem(device.name.c_str(), NULL)){
        this->draw_device_info(device);
        this->draw_device_queue_families(device);

        ImGui::EndTabItem();
      }

    }
    ImGui::EndTabBar();
  }

  //---------------------------
}

//Subfunction
void Device::draw_device_info(prf::hardware::Device& device){
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
  ImGui::TextColored(color, "%d", device.vendor_ID);

  //Discrete GPU
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Discrete GPU"); ImGui::TableNextColumn();
  const char* discrete = device.discrete_gpu ? "true" : "false";
  ImGui::TextColored(color, "%s", discrete);

  //Extension support
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Extension support"); ImGui::TableNextColumn();
  const char* support = device.has_extension_support ? "true" : "false";
  ImGui::TextColored(color, "%s", support);

  //Max image
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Max image"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d", device.max_image_dim);

  ImGui::EndTable();

  //---------------------------
}
void Device::draw_device_queue_families(prf::hardware::Device& device){
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

  //Queue count
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Queue");
  for(int i=0; i<device.vec_queue_family.size(); i++){
    ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", device.vec_queue_family[i].nb_queue);
  }

  //Graphics queue
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Graphics");
  for(int i=0; i<device.vec_queue_family.size(); i++){
    ImGui::TableNextColumn();
    if(device.vec_queue_family[i].graphics) ImGui::TextColored(color, "X");
  }

  //Compute queue
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Compute");
  for(int i=0; i<device.vec_queue_family.size(); i++){
    ImGui::TableNextColumn();
    if(device.vec_queue_family[i].compute) ImGui::TextColored(color, "X");
  }

  //Transfer queue
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Transfer");
  for(int i=0; i<device.vec_queue_family.size(); i++){
    ImGui::TableNextColumn();
    if(device.vec_queue_family[i].transfer) ImGui::TextColored(color, "X");
  }

  //Sparse binding queue
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Sparse binding");
  for(int i=0; i<device.vec_queue_family.size(); i++){
    ImGui::TableNextColumn();
    if(device.vec_queue_family[i].sparseBinding) ImGui::TextColored(color, "X");
  }

  //Presentation queue
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Presentation");
  for(int i=0; i<device.vec_queue_family.size(); i++){
    ImGui::TableNextColumn();
    if(device.vec_queue_family[i].presentation) ImGui::TextColored(color, "X");
  }

  ImGui::EndTable();

  //---------------------------
}

}
