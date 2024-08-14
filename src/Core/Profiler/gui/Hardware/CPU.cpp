#include "CPU.h"

#include <Core/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace prf::gui::hardware{

//Constructor / Destructor
CPU::CPU(prf::Node* node_profiler){
  //---------------------------

  this->prf_struct = node_profiler->get_prf_struct();
  this->prf_hardware = node_profiler->get_prf_hardware();

  //---------------------------
}
CPU::~CPU(){}

//Main function
void CPU::draw_tab(){
  //---------------------------

  prf_hardware->loop();

  this->draw_cpu_info();

  //---------------------------
}

//Subfunction
void CPU::draw_cpu_info(){
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  ImGui::BeginTable("profiler_panel##info", 2);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 125.0f);

  //Device
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Device"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", prf_struct->hardware.cpu.name.c_str());

  //Temperature
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Temperature"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%.2f°", prf_struct->hardware.cpu.temperature);
  ImGui::SameLine();
  ImGui::Text("[%d°]", prf_struct->hardware.cpu.temperature_max);

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}

}
