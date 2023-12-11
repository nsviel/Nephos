#include "Profiler.h"

#include <GUI.h>
#include <Vulkan.h>
#include <VK_main/VK_info.h>
#include <Engine.h>


namespace gui::rnd::engine{

//Constructor / Destructor
Profiler::Profiler(GUI* gui, bool* show_window, string name) : Panel(show_window, name){
  //---------------------------

  Engine* engine = gui->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->gui = gui;
  this->vk_info = eng_vulkan->get_vk_info();

  this->width = 150;

  //---------------------------
}
Profiler::~Profiler(){}

//Main function
void Profiler::design_panel(){
  //---------------------------

  this->design_profiling();

  //---------------------------
}

//Subfunctions
void Profiler::design_profiling(){
  ImGui::BeginChild("Profiling", ImVec2(0, 150), false);
  //---------------------------

  this->device_model();
  bool update = time_update();
  this->time_drawig(update);
  this->time_general(update);

  //---------------------------
  ImGui::EndChild();
}
void Profiler::device_model(){
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  if(ImGui::BeginTable("render##device", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 125.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Device model"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", vk_info->get_gpu_name().c_str());

    ImGui::EndTable();
  }

  //---------------------------
}
bool Profiler::time_update(){
  //---------------------------

  static timer_time t1 = timer.start_t();
  float duration = timer.stop_ms(t1) / 1000;
  if(duration >= 0.5){
    t1 = timer.start_t();
    return true;
  }

  //---------------------------
  return false;
}
void Profiler::time_drawig(bool update){
  ImGuiIO io = ImGui::GetIO();
  //---------------------------

  static float mean_draw_frame = 0;
  static float meanr_rp_scene = 0;
  static float meanr_rp_edl = 0;
  static float meanr_rp_gui = 0;

  //mETTRE DES TABLEASU ICI !!!!!
  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  if(ImGui::BeginTable("render##time", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 125.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Frame drawing"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.1f ms", mean_draw_frame);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Renderpass scene"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.1f ms", meanr_rp_scene);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Renderpass EDL"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.1f ms", meanr_rp_edl);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Renderpass GUI"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.1f ms", meanr_rp_gui);

    ImGui::EndTable();
  }

  //---------------------------
}
void Profiler::time_general(bool update){
  ImGuiIO io = ImGui::GetIO();
  //---------------------------

  float time_init = 0;

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  if(ImGui::BeginTable("render##device", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 125.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Initialization"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.1f ms", time_init);

    ImGui::EndTable();
  }

  //FPS
  ImGui::Text(" ");
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", 1000.0f / vk_info->get_fps());
  ImGui::SameLine();
  ImGui::Text(" ms/frame [");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", vk_info->get_fps()); //io.Framerate
  ImGui::SameLine();
  ImGui::Text(" FPS ]");

  //---------------------------
}

}
