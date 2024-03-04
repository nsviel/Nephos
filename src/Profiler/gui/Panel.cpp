#include "Panel.h"

#include <Profiler/Namespace.h>
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

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(FLT_MAX, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){
      this->design_panel();
      ImGui::End();
    }
    ImGui::PopStyleVar();
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
  if(ImGui::BeginTable("profiler_panel##info", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);

    //GPU device
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Device"); ImGui::TableNextColumn();
    prf::vulkan::Profiler* profiler_vulkan = prf_manager->get_profiler_vulkan();
    string gpu = profiler_vulkan->get_info()->selected_gpu;
    ImGui::TextColored(color, "%s", gpu.c_str());

    //Selected tasker
    if(selected_profiler != nullptr){
      selected_profiler->show_info();
    }

    ImGui::EndTable();
  }

  //---------------------------
}
void Panel::main_button(){
  bool& pause = gui_graph->get_pause();
  //---------------------------

  //Play button -> if paused
  if(pause){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, 255));
    if(ImGui::Button(ICON_FA_PLAY "##profiler_play")){
      pause = false;
    }
    ImGui::PopStyleColor();
  }
  //Pause button -> if not paused
  else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(45, 133, 133, 255));
    if(ImGui::Button(ICON_FA_PAUSE "##profiler_pause")){
      pause = true;
    }
    ImGui::PopStyleColor();
  }

  //Graph max time
  ImGui::SameLine();
  ImGui::SetNextItemWidth(150);
  if(ImGui::SliderInt("Y axis", &max_time, 10, 100, "%d ms")){
    gui_graph->set_graphs_max_time(max_time);
  }

  //---------------------------
}
void Panel::draw_profiler(){
  std::list<prf::type::Profiler*> list_profiler = prf_manager->get_list_profiler();
  //---------------------------

  if(ImGui::BeginTabBar("profiler_panel##graph")){
    for(int i=0; i<list_profiler.size(); i++){
      prf::type::Profiler* profiler = *next(list_profiler.begin(), i);

      ImGui::SetNextItemWidth(100);
      if(ImGui::BeginTabItem(profiler->get_name().c_str())){

        //Vulkan tab
        if(prf::vulkan::Profiler* vulkan = dynamic_cast<prf::vulkan::Profiler*>(profiler)){
          this->selected_profiler = gui_vulkan;
          gui_vulkan->draw_profiler(vulkan);
        }
        //Graph tab
        else if(prf::graph::Profiler* graph = dynamic_cast<prf::graph::Profiler*>(profiler)){
          this->selected_profiler = gui_graph;
          gui_graph->draw_profiler(graph);
        }
        ImGui::EndTabItem();
      }
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}

}
