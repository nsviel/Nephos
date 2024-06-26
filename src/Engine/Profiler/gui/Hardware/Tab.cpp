#include "Tab.h"

#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace prf::gui::hardware{

//Constructor / Destructor
Tab::Tab(prf::Node* node_profiler){
  //---------------------------



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
      this->draw_tab_gpu(prf_struct, dimension);
      ImGui::EndTabItem();
    }

    //Device tab
    ImGui::SetNextItemWidth(100);
    if(ImGui::BeginTabItem("Devices##profiler_vulkan", NULL)){
      this->draw_tab_device(prf_struct, dimension);
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}

//Tab function
void Tab::draw_tab_device(prf::hardware::Structure* prf_struct, ImVec2 dimension){
  //---------------------------

  if(ImGui::BeginTabBar("vulkan_device##tab_bar")){
    for(int i=0; i<prf_struct->vec_device.size(); i++){
      prf::hardware::Device& device = prf_struct->vec_device[i];

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
void Tab::draw_tab_gpu(prf::hardware::Structure* prf_struct, ImVec2 dimension){
  //---------------------------

  this->draw_gpu_info(prf_struct);
  this->draw_gpu_queue(prf_struct);

  //---------------------------
}

//Subfunction
void Tab::draw_device_info(prf::hardware::Device& device){
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
void Tab::draw_device_queue_families(prf::hardware::Device& device){
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
void Tab::draw_gpu_info(prf::hardware::Structure* prf_struct){
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  ImGui::BeginTable("profiler_panel##info", 2);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 75.0f);

  //Device
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Device"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", prf_struct->gpu.name.c_str());

  //Temperature
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Temperature"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d°", prf_struct->gpu.temperature);

  //Consumption
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Total consumption"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%.2f J", prf_struct->gpu.total_consumption);

  //Power
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Power usage"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d W", prf_struct->gpu.power_usage);

  //Fan speed
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Fan speed"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d rpm", prf_struct->gpu.fan_speed);

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Tab::draw_gpu_queue(prf::hardware::Structure* prf_struct){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Queue");

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_BordersV;
  flags |= ImGuiTableFlags_BordersOuterH;
  flags |= ImGuiTableFlags_RowBg;
  flags |= ImGuiTableFlags_ContextMenuInBody;
  ImGui::BeginTable("vulkan_queue##table", 4, flags);

  //Family index
  ImGui::TableSetupColumn("");
  ImGui::TableSetupColumn("Number");
  ImGui::TableSetupColumn("Family");
  ImGui::TableSetupColumn("Thread");
  ImGui::TableHeadersRow();

  for(int i=0; i<prf_struct->gpu.vec_queue.size(); i++){
    prf::hardware::Queue& queue = prf_struct->gpu.vec_queue[i];

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    switch(queue.type){
      case prf::hardware::queue::GRAPHICS:{
        ImGui::Text("Graphics");
        break;
      }
      case prf::hardware::queue::PRESENTATION:{
        ImGui::Text("Presentation");
        break;
      }
      case prf::hardware::queue::TRANSFER:{
        ImGui::Text("Transfer");
        break;
      }
    }
    ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", queue.number);
    ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", queue.family_ID);
    ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", queue.thread_ID.c_str());
  }

  ImGui::EndTable();

  //---------------------------
}

}
