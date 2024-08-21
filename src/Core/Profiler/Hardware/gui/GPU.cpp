#include "GPU.h"

#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>


namespace prf::gui::hardware{

//Constructor / Destructor
GPU::GPU(prf::hardware::Node* node_hardware){
  //---------------------------

  this->prf_struct = node_hardware->get_prf_struct();
  this->prf_manager = node_hardware->get_prf_manager();

  //---------------------------
}
GPU::~GPU(){}

//Main function
void GPU::draw_tab(){
  //---------------------------

  prf_manager->loop();

  this->draw_gpu_info();
  this->draw_gpu_queue();

  //---------------------------
}

//Subfunction
void GPU::draw_gpu_info(){
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  ImGui::BeginTable("profiler_panel##info", 2);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 125.0f);

  //Device
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Device"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", prf_struct->hardware.gpu.name.c_str());

  //Temperature
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Temperature"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d°", prf_struct->hardware.gpu.temperature);
  ImGui::SameLine();
  ImGui::Text("[%d°]", prf_struct->hardware.gpu.temperature_max);

  //Consumption
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Total consumption"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%.2f kJ", prf_struct->hardware.gpu.total_consumption);

  //Power
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Power usage"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%.2f W", prf_struct->hardware.gpu.power_usage);

  //Fan speed
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Fan speed"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d rpm", prf_struct->hardware.gpu.fan_speed);

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void GPU::draw_gpu_queue(){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Queue");

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_BordersV;
  flags |= ImGuiTableFlags_BordersOuterH;
  flags |= ImGuiTableFlags_RowBg;
  flags |= ImGuiTableFlags_ContextMenuInBody;
  ImGui::BeginTable("vulkan_queue##table", 5, flags);

  //Family index
  ImGui::TableSetupColumn("");
  ImGui::TableSetupColumn("Number");
  ImGui::TableSetupColumn("Family");
  ImGui::TableSetupColumn("Index");
  ImGui::TableSetupColumn("Thread");
  ImGui::TableHeadersRow();

  for(int i=0; i<prf_struct->hardware.gpu.vec_queue.size(); i++){
    prf::hardware::structure::Queue& queue = prf_struct->hardware.gpu.vec_queue[i];

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    switch(queue.type){
      case prf::hardware::structure::queue::GRAPHICS:{
        ImGui::Text("Graphics");
        break;
      }
      case prf::hardware::structure::queue::PRESENTATION:{
        ImGui::Text("Presentation");
        break;
      }
      case prf::hardware::structure::queue::TRANSFER:{
        ImGui::Text("Transfer");
        break;
      }
    }
    ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", queue.number);
    ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", queue.family_ID);
    ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", queue.family_idx);
    ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", queue.thread_ID.c_str());
  }

  ImGui::EndTable();

  //---------------------------
}

}
