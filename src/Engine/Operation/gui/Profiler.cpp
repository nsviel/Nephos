#include "Profiler.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace eng::render::gui{

//Constructor / Destructor
Profiler::Profiler(eng::Node* node_engine, bool* show_window){
  //---------------------------

  vk::Node* eng_vulkan = node_engine->get_eng_vulkan();

  this->node_engine = node_engine;
  this->node_utility = node_engine->get_node_utility();
  this->gui_cpu = new utl::improfil::Manager("cpu");
  this->gui_gpu = new utl::improfil::Manager("gpu");
  this->gui_capture = new utl::improfil::Manager("capture");
  this->vk_info = eng_vulkan->get_vk_info();

  this->show_window = show_window;
  this->name = "Profiler";
  this->width = 150;
  this->pause = false;

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

  this->main_info();
  this->main_button();
  this->draw_graph();
  this->draw_timeline();

  //---------------------------
}

//Subfunction
void Profiler::main_info(){
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  if(ImGui::BeginTable("render##device", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);

    //GPU device
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Device"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", vk_info->get_gpu_name().c_str());

    //Main loop fps
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Loop"); ImGui::TableNextColumn();
    utl::element::Profiler* profiler = node_utility->get_cpu_profiler();
    ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", 1000.0f / profiler->get_fps());
    ImGui::SameLine();
    ImGui::Text(" ms/frame [");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", profiler->get_fps()); //io.Framerate
    ImGui::SameLine();
    ImGui::Text(" FPS ]");

    ImGui::EndTable();
  }

  //---------------------------
}
void Profiler::main_button(){
  //---------------------------

  //Play button -> if paused or not playing
  if(pause){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, 255));
    if(ImGui::Button(ICON_FA_PLAY "##profiler_play")){
      this->pause = false;
    }
    ImGui::PopStyleColor();
  }
  //Pause button -> if not paused and playing
  else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(45, 133, 133, 255));
    if(ImGui::Button(ICON_FA_PAUSE "##profiler_pause")){
      this->pause = true;
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Profiler::draw_graph(){
  //---------------------------

  if(ImGui::BeginTabBar("device_tab##4567")){
    ImVec2 dimension = ImGui::GetContentRegionAvail();

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("All##4568", NULL)){
      dimension = ImVec2(dimension.x, dimension.y/3 - 3.33);
      this->draw_profiler_cpu(dimension);
      this->draw_profiler_gpu(dimension);
      this->draw_profiler_capture(dimension);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("CPU##4567", NULL)){
      this->draw_profiler_cpu(dimension);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if(ImGui::BeginTabItem("GPU##4567", NULL)){
      this->draw_profiler_gpu(dimension);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Capture##4567", NULL)){
      this->draw_profiler_capture(dimension);
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}

//Profiler graphs
void Profiler::draw_profiler_cpu(ImVec2 dimensions){
  utl::element::Profiler* profiler = node_utility->get_cpu_profiler();
  //---------------------------

  if(!pause){
    //Reset graph
    gui_cpu->reset();

    //Assign tasks
    vector<utl::type::Task>& vec_gpu_task = profiler->get_vec_task();
    for(int i=0; i<vec_gpu_task.size(); i++){
      utl::type::Task task = vec_gpu_task[i];
      gui_cpu->add_task(task.time_beg, task.time_end, task.name);
    }

    //load data
    gui_cpu->load_data_to_graph();
  }

  //Render profiler
  gui_cpu->render_child(dimensions);

  //---------------------------
}
void Profiler::draw_profiler_gpu(ImVec2 dimensions){
  utl::element::Profiler* profiler = node_utility->get_gpu_profiler();
  //---------------------------

  if(!pause){
    //Reset graph
    gui_gpu->reset();

    //Assign tasks
    vector<utl::type::Task>& vec_gpu_task = profiler->get_vec_task();
    for(int i=0; i<vec_gpu_task.size(); i++){
      utl::type::Task task = vec_gpu_task[i];
      gui_gpu->add_task(task.time_beg, task.time_end, task.name);
    }

    //load data
    gui_gpu->load_data_to_graph();
  }

  //Render profiler
  gui_gpu->render_child(dimensions);

  //---------------------------
}
void Profiler::draw_profiler_capture(ImVec2 dimensions){
  //---------------------------

  eng::capture::Node* node_capture = node_engine->get_node_capture();
  eng::k4n::Node* node_k4n = node_capture->get_node_k4n();
  eng::k4n::dev::Swarm* k4n_swarm = node_k4n->get_k4n_swarm();
  eng::k4n::dev::Master* master = k4n_swarm->get_selected_master();


  if(eng::k4n::dev::Sensor* sensor = dynamic_cast<eng::k4n::dev::Sensor*>(master->selected_entity)){
    utl::element::Profiler* profiler = sensor->cap_profiler;

    if(!pause){
      //Reset graph
      gui_capture->reset();

      //Assign tasks
      vector<utl::type::Task>& vec_task = profiler->get_vec_task();
      for(int i=0; i<vec_task.size(); i++){
        utl::type::Task task = vec_task[i];
        gui_capture->add_task(task.time_beg, task.time_end, task.name);
      }

      //load data
      gui_capture->load_data_to_graph();
    }

    //Render profiler
    gui_capture->render_child(dimensions);
  }

  //---------------------------
}
void Profiler::draw_timeline(){
  //---------------------------


  //---------------------------
}


}
