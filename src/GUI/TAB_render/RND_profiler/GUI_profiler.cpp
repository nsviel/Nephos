#include "GUI_profiler.h"

#include <GUI.h>
#include <Vulkan.h>
#include <VK_main/VK_info.h>
#include <Engine.h>


//Constructor / Destructor
GUI_profiler::GUI_profiler(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  Engine* engine = gui->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->gui = gui;
  this->vk_info = eng_vulkan->get_vk_info();

  this->width = 150;

  //---------------------------
}
GUI_profiler::~GUI_profiler(){}

//Main function
void GUI_profiler::design_panel(){
  //---------------------------

  this->design_profiling();

  //---------------------------
}

//Subfunctions
void GUI_profiler::design_profiling(){
  ImGui::BeginChild("Profiling", ImVec2(0, 150), false);
  //---------------------------

  ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f),"Profiling");

  this->device_model();

  bool update = time_update();
  this->time_drawig(update);
  this->time_general(update);

  //---------------------------
  ImGui::EndChild();
}
void GUI_profiler::device_model(){
  //---------------------------

  ImGui::Text("Device model ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%s", vk_info->get_gpu_name().c_str());

  //---------------------------
}
bool GUI_profiler::time_update(){
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
void GUI_profiler::time_drawig(bool update){
  ImGuiIO io = ImGui::GetIO();
  //---------------------------

  static float mean_draw_frame = 0;
  static float meanr_rp_scene = 0;
  static float meanr_rp_edl = 0;
  static float meanr_rp_gui = 0;
  if(update){

  }

  ImGui::Text("Time draw frame ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", mean_draw_frame);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //Time init
  ImGui::Text("Time renderpass scene ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", meanr_rp_scene);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //Time init
  ImGui::Text("Time renderpass EDL ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", meanr_rp_edl);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //Time init
  ImGui::Text("Time renderpass ui ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", meanr_rp_gui);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //---------------------------
}
void GUI_profiler::time_general(bool update){
  ImGuiIO io = ImGui::GetIO();
  //---------------------------

  //Time init
  ImGui::Text("Time initialization ");
  ImGui::SameLine();
  //ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", struct_vulkan->info.engine_init);
  ImGui::SameLine();
  ImGui::Text(" ms");

  //FPS
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", 1000.0f / vk_info->get_fps());
  ImGui::SameLine();
  ImGui::Text(" ms/frame [");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", vk_info->get_fps()); //io.Framerate
  ImGui::SameLine();
  ImGui::Text(" FPS ]");

  //---------------------------
}
