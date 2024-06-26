#include "Vulkan.h"

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
void Vulkan::show_profiler(prf::base::Profiler* profiler){
  //---------------------------

  //Retrieve vulkan info struct
  prf::vulkan::Profiler* prf_vulkan = dynamic_cast<prf::vulkan::Profiler*>(profiler);
  if(prf_vulkan == nullptr) return;
  prf::vulkan::Structure* prf_struct = prf_vulkan->get_prf_struct();

  //Draw general info
  this->draw_info(prf_struct);
  this->draw_tab(prf_struct);

  //---------------------------
}

//Tab function
void Vulkan::draw_info(prf::vulkan::Structure* prf_struct){
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  ImGui::BeginTable("profiler_panel##info", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);

  //GPU device
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Device"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", prf_struct->selected_device.name.c_str());

  ImGui::EndTable();

  //---------------------------
}
void Vulkan::draw_tab(prf::vulkan::Structure* prf_struct){
  //---------------------------

  //Draw specific info
  if(ImGui::BeginTabBar("Vulkan##profiler_vulkan")){
    ImVec2 dimension = ImGui::GetContentRegionAvail();

    //Device tab
    ImGui::SetNextItemWidth(100);
    if(ImGui::BeginTabItem("Device##profiler_vulkan", NULL)){
      this->draw_tab_device(prf_struct, dimension);
      ImGui::EndTabItem();
    }

    //Queue tab
    ImGui::SetNextItemWidth(100);
    if(ImGui::BeginTabItem("Queue##profiler_vulkan", NULL)){
      this->draw_tab_queue(prf_struct, dimension);
      ImGui::EndTabItem();
    }

    //Thread tab
    ImGui::SetNextItemWidth(100);
    if(ImGui::BeginTabItem("Thread##profiler_vulkan", NULL)){
      this->draw_tab_thread(prf_struct, dimension);
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}
void Vulkan::draw_tab_device(prf::vulkan::Structure* prf_struct, ImVec2 dimension){
  //---------------------------

  if(ImGui::BeginTabBar("vulkan_device##tab_bar")){
    for(int i=0; i<prf_struct->vec_device.size(); i++){
      prf::vulkan::Device& device = prf_struct->vec_device[i];

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
void Vulkan::draw_tab_queue(prf::vulkan::Structure* prf_struct, ImVec2 dimension){
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_BordersV;
  flags |= ImGuiTableFlags_BordersOuterH;
  flags |= ImGuiTableFlags_RowBg;
  flags |= ImGuiTableFlags_ContextMenuInBody;
  ImGui::BeginTable("vulkan_queue##table", 3, flags);

  //Family index
  ImGui::TableSetupColumn("");
  ImGui::TableSetupColumn("Number");
  ImGui::TableSetupColumn("Family");
  ImGui::TableHeadersRow();

  //Graphics
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Graphics");
  ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d", prf_struct->map_queue[prf::vulkan::queue::GRAPHICS].number);
  ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d", prf_struct->map_queue[prf::vulkan::queue::GRAPHICS].ID_family);

  //Presentation
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Presentation");
  ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d", prf_struct->map_queue[prf::vulkan::queue::PRESENTATION].number);
  ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d", prf_struct->map_queue[prf::vulkan::queue::PRESENTATION].ID_family);

  //Transfer
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Transfer");
  ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d", prf_struct->map_queue[prf::vulkan::queue::TRANSFER].number);
  ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d", prf_struct->map_queue[prf::vulkan::queue::TRANSFER].ID_family);

  ImGui::EndTable();

  //---------------------------
}
void Vulkan::draw_tab_thread(prf::vulkan::Structure* prf_struct, ImVec2 dimension){
  //---------------------------

  ImVec4 green = ImVec4(0.5, 1, 0.5, 1);
  ImVec4 blue = ImVec4(0.5, 0.5, 1, 1);
  static ImGuiTableFlags flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_RowBg | ImGuiTableFlags_ContextMenuInBody;
  ImGui::BeginTable("vulkan_thread##table", 2, flags);

  ImGui::TableSetupColumn("Name");
  ImGui::TableSetupColumn("ID");
  ImGui::TableHeadersRow();

  for(int i=0; i<prf_struct->vec_thread.size(); i++){
    prf::vulkan::Thread& thread = prf_struct->vec_thread[i];

    //Thread name
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::TextColored(green, "%s", thread.name.c_str());

    //Thread ID
    ImGui::TableNextColumn();
    ImGui::TextColored(blue, "%s", thread.ID.c_str());
  }

  ImGui::EndTable();

  //---------------------------
}

//Subfunction
void Vulkan::draw_device_info(prf::vulkan::Device& device){
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
void Vulkan::draw_device_queue_families(prf::vulkan::Device& device){
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
