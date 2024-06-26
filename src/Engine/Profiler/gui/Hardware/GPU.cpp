#include "GPU.h"

#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace prf::gui::hardware{

//Constructor / Destructor
GPU::GPU(prf::Node* node_profiler){
  //---------------------------



  //---------------------------
}
GPU::~GPU(){}

//Main function
void GPU::draw_tab(prf::hardware::Structure* prf_struct, ImVec2 dimension){
  //---------------------------

  this->draw_gpu_info(prf_struct);
  this->draw_gpu_queue(prf_struct);

  //---------------------------
}

//Subfunction
void GPU::draw_gpu_info(prf::hardware::Structure* prf_struct){
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
void GPU::draw_gpu_queue(prf::hardware::Structure* prf_struct){
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
