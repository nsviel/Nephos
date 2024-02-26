#include "Panel.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace prf::gui{

//Constructor / Destructor
Panel::Panel(prf::Node* node_profiler, bool* show_window){
  //---------------------------

  this->prf_manager = node_profiler->get_prf_manager();
  this->gui_vulkan = new prf::gui::Vulkan(node_profiler);
  this->gui_graph = new prf::gui::Graph(node_profiler);

  this->show_window = show_window;
  this->name = "Profiler";
  this->width = 150;
  this->pause = false;

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
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
void Panel::design_panel(){
  //---------------------------

  this->main_info();
  this->main_button();
  this->draw_profiler();

  //---------------------------
}

//Subfunction
void Panel::main_info(){
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  if(ImGui::BeginTable("render##device", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);

    //GPU device
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Device"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", gpu.c_str());

    //Selected tasker
    if(selected_tasker != nullptr){
      //Type
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Type"); ImGui::TableNextColumn();
      //ImGui::TextColored(color, "%s", selected_tasker->get_type().c_str());

      //FPS
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Loop"); ImGui::TableNextColumn();
      ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", 1000.0f / selected_tasker->get_loop_fps());
      ImGui::SameLine();
      ImGui::Text(" ms/frame [");
      ImGui::SameLine();
      ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", selected_tasker->get_loop_fps()); //io.Framerate
      ImGui::SameLine();
      ImGui::Text(" FPS ]");
    }

    ImGui::EndTable();
  }

  //---------------------------
}
void Panel::main_button(){
  //---------------------------

  //Play button -> if paused
  if(pause){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, 255));
    if(ImGui::Button(ICON_FA_PLAY "##profiler_play")){
      this->pause = false;
    }
    ImGui::PopStyleColor();
  }
  //Pause button -> if not paused
  else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(45, 133, 133, 255));
    if(ImGui::Button(ICON_FA_PAUSE "##profiler_pause")){
      this->pause = true;
    }
    ImGui::PopStyleColor();
  }

  //Graph max time
  ImGui::SameLine();
  ImGui::SetNextItemWidth(150);
  if(ImGui::SliderInt("Y axis", &max_time, 10, 100, "%d ms")){
    this->set_graphs_max_time(max_time);
  }

  //---------------------------
}
void Panel::draw_profiler(){
  std::list<prf::type::Profiler*> list_profiler = prf_manager->get_list_profiler();
  //---------------------------

  if(ImGui::BeginTabBar("profiler_gui##4567")){
    for(int i=0; i<list_profiler.size(); i++){
      prf::type::Profiler* profiler = *next(list_profiler.begin(), i);

      ImGui::SetNextItemWidth(100);
      if(ImGui::BeginTabItem(profiler->get_name().c_str())){
        //Vulkan tab
        if(prf::vulkan::Profiler* vulkan = dynamic_cast<prf::vulkan::Profiler*>(profiler)){
          gui_vulkan->draw_graph(vulkan);
        }
        //Graph tab
        else if(prf::graph::Profiler* graph = dynamic_cast<prf::graph::Profiler*>(profiler)){
          gui_graph->draw_graph(graph);
        }
        ImGui::EndTabItem();
      }
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}
void Panel::set_graphs_max_time(int& value){
  std::list<prf::type::Profiler*> list_profiler = prf_manager->get_list_profiler();
  //---------------------------

  if(ImGui::BeginTabBar("profiler_gui##4567")){
    for(int i=0; i<list_profiler.size(); i++){
      prf::type::Profiler* profiler = *next(list_profiler.begin(), i);

      if(prf::graph::Profiler* profiler = dynamic_cast<prf::graph::Profiler*>(profiler)){
        vector<prf::graph::Tasker*> vec_tasker = profiler->get_vec_tasker();

        for(int i=0; i<vec_tasker.size(); i++){
          prf::graph::Tasker* tasker = vec_tasker[i];
          prf::improfil::Manager* gui_graph = tasker->get_gui_graph();

          gui_graph->set_time_max(max_time);
        }
      }
    }
  }

  //---------------------------
}

}
