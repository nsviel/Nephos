#include "Profiler.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace eng::render::gui{

//Constructor / Destructor
Profiler::Profiler(eng::render::Node* node_render, bool* show_window){
  //---------------------------

  eng::Node* engine = node_render->get_node_engine();
  vk::Node* eng_vulkan = engine->get_eng_vulkan();

  this->cpu_profiler = new utl::improfil::Manager("cpu");
  this->gpu_profiler = new utl::improfil::Manager("gpu");
  this->cap_profiler = new utl::improfil::Manager("capture");
  this->vk_info = eng_vulkan->get_vk_info();

  this->show_window = show_window;
  this->name = "Profiler";
  this->width = 150;

  //---------------------------
}
Profiler::~Profiler(){}

//Main function
void Profiler::run_panel(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){
      this->design_panel();
      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Profiler::design_panel(){
  //---------------------------

  this->device_model();
  this->main_loop_fps();
  this->draw_graph();

  //---------------------------
}

//Subfunction
void Profiler::device_model(){
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  if(ImGui::BeginTable("render##device", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Device"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", vk_info->get_gpu_name().c_str());

    ImGui::EndTable();
  }

  //---------------------------
}
void Profiler::main_loop_fps(){
  ImGuiIO io = ImGui::GetIO();
  //---------------------------

  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", 1000.0f / vk_info->get_fps());
  ImGui::SameLine();
  ImGui::Text(" ms/frame [");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", vk_info->get_fps()); //io.Framerate
  ImGui::SameLine();
  ImGui::Text(" FPS ]");

  //---------------------------
}
void Profiler::draw_graph(){
  //---------------------------

  if(ImGui::BeginTabBar("device_tab##4567")){
    ImVec2 image_size = ImGui::GetContentRegionAvail();

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("All##4568", NULL)){
      image_size = ImVec2(image_size.x, image_size.y/3-3.33);
      this->draw_profiler_cpu(image_size);
      this->draw_profiler_gpu(image_size);
      this->draw_profiler_capture(image_size);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("CPU##4567", NULL)){
      this->draw_profiler_cpu(image_size);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if(ImGui::BeginTabItem("GPU##4567", NULL)){
      this->draw_profiler_gpu(image_size);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Capture##4567", NULL)){
      this->draw_profiler_capture(image_size);
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}

//Profiler graphs
void Profiler::draw_profiler_cpu(ImVec2 dimensions){
  //---------------------------

  //Reset graph
  cpu_profiler->reset();

  //Assign tasks
  vector<vk::structure::Task>& vec_gpu_task = vk_info->get_profiler_data();
  for(int i=0; i<vec_gpu_task.size(); i++){
    vk::structure::Task task = vec_gpu_task[i];
    cpu_profiler->add_task(task.time_beg, task.time_end, task.name);
  }

  //Render graph
  ImVec2 available_size = ImGui::GetContentRegionAvail();
  available_size.y = available_size.y / 2 - 2.5;
  cpu_profiler->render_child(available_size);

  //---------------------------
}
void Profiler::draw_profiler_gpu(ImVec2 dimensions){
  //---------------------------

  //Reset graph
  gpu_profiler->reset();

  //Assign tasks
  vector<vk::structure::Task>& vec_gpu_task = vk_info->get_profiler_data();
  for(int i=0; i<vec_gpu_task.size(); i++){
    vk::structure::Task task = vec_gpu_task[i];
    gpu_profiler->add_task(task.time_beg, task.time_end, task.name);
  }

  //Render graph
  ImVec2 available_size = ImGui::GetContentRegionAvail();
  available_size.y = available_size.y / 2 - 2.5;
  gpu_profiler->render_child(available_size);

  //---------------------------
}
void Profiler::draw_profiler_capture(ImVec2 dimensions){
  //---------------------------

  //Reset graph
  cap_profiler->reset();

  //Assign tasks
  vector<vk::structure::Task>& vec_gpu_task = vk_info->get_profiler_data();
  for(int i=0; i<vec_gpu_task.size(); i++){
    vk::structure::Task task = vec_gpu_task[i];
    cap_profiler->add_task(task.time_beg, task.time_end, task.name);
  }

  //Render graph
  ImVec2 available_size = ImGui::GetContentRegionAvail();
  available_size.y = available_size.y / 2 - 2.5;
  cap_profiler->render_child(available_size);

  //---------------------------
}


}
