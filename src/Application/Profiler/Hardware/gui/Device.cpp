#include "Device.h"

#include <Hardware/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>


namespace prf::gui::hardware{

//Constructor / Destructor
Device::Device(prf::hardware::Node* node_hardware){
  //---------------------------

  this->prf_struct = node_hardware->get_prf_struct();

  //---------------------------
}
Device::~Device(){}

//Main function
void Device::draw_tab(){
  //---------------------------

  if(ImGui::BeginTabBar("vulkan_device##tab_bar")){
    for(auto& device : prf_struct->vec_device){
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
void Device::draw_device_info(prf::hardware::structure::Device& device){
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  ImGui::BeginTable("vulkan_device##table", 2);

  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 125.0f);

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
void Device::draw_device_queue_families(prf::hardware::structure::Device& device){
  //---------------------------

  int size = device.vec_queue_family.size() + 2;
  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  ImGuiTableFlags flag;
  flag |= ImGuiTableFlags_BordersV;
  flag |= ImGuiTableFlags_BordersOuterH;
  flag |= ImGuiTableFlags_RowBg;
  flag |= ImGuiTableFlags_ContextMenuInBody;
  ImGui::BeginTable("vulkan_thread##table", size, flag);

  //Family index
  ImGui::TableSetupColumn("Family", ImGuiTableColumnFlags_WidthFixed, 125.0f);
  for(int i=0; i<device.vec_queue_family.size(); i++){
    ImGui::TableSetupColumn(std::to_string(i).c_str(), ImGuiTableColumnFlags_WidthFixed, 25.0f);
  }
  ImGui::TableSetupColumn("");
  ImGui::TableHeadersRow();

  //Queue count
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Queue");
  for(auto& queue_family : device.vec_queue_family){
    ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", queue_family.nb_queue);
  }

  //Graphics queue
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Graphics");
  for(auto& queue_family : device.vec_queue_family){
    ImGui::TableNextColumn();
    if(queue_family.graphics) ImGui::TextColored(color, "X");
  }

  //Compute queue
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Compute");
  for(auto& queue_family : device.vec_queue_family){
    ImGui::TableNextColumn();
    if(queue_family.compute) ImGui::TextColored(color, "X");
  }

  //Transfer queue
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Transfer");
  for(auto& queue_family : device.vec_queue_family){
    ImGui::TableNextColumn();
    if(queue_family.transfer) ImGui::TextColored(color, "X");
  }

  //Sparse binding queue
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Sparse binding");
  for(auto& queue_family : device.vec_queue_family){
    ImGui::TableNextColumn();
    if(queue_family.sparseBinding) ImGui::TextColored(color, "X");
  }

  //Presentation queue
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Presentation");
  for(auto& queue_family : device.vec_queue_family){
    ImGui::TableNextColumn();
    if(queue_family.presentation) ImGui::TextColored(color, "X");
  }

  ImGui::TableNextColumn();

  ImGui::EndTable();

  //---------------------------
}

}
