#include "Panel.h"

#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace prf::gui{

//Constructor / Destructor
Panel::Panel(prf::Node* node_profiler, bool* show_window){
  //---------------------------

  this->prf_manager = node_profiler->get_prf_manager();
  this->gui_vulkan = new prf::gui::Vulkan(node_profiler);
  this->gui_graph = new prf::gui::Graph(node_profiler);
  this->gui_hardware = new prf::gui::Hardware(node_profiler);

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
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(600, 600));
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
  ImGui::BeginTable("profiler_panel##info", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);

  //GPU device
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Device"); ImGui::TableNextColumn();
  prf::vulkan::Profiler* profiler_vulkan = prf_manager->get_profiler_vulkan();
  string gpu = gui_vulkan->get_selected_gpu_name(profiler_vulkan);
  ImGui::TextColored(color, "%s", gpu.c_str());

  //Selected tasker
  if(selected_profiler != nullptr){
    selected_profiler->show_info();
  }

  ImGui::EndTable();

  //---------------------------
}
void Panel::main_button(){
  //---------------------------

  if(selected_profiler != nullptr){
    selected_profiler->show_command();
  }

  //---------------------------
}
void Panel::draw_profiler(){
  std::list<prf::base::Profiler*> list_profiler = prf_manager->get_list_profiler();
  //---------------------------

  if(ImGui::BeginTabBar("profiler_panel##graph")){
    for(int i=0; i<list_profiler.size(); i++){
      prf::base::Profiler* profiler = *next(list_profiler.begin(), i);

      ImGui::SetNextItemWidth(100);
      if(ImGui::BeginTabItem(profiler->name.c_str())){

        //Graph tab
        if(prf::graph::Profiler* graph = dynamic_cast<prf::graph::Profiler*>(profiler)){
          this->selected_profiler = gui_graph;
          gui_graph->draw_profiler(graph);
        }
        //Vulkan tab
        else if(prf::vulkan::Profiler* vulkan = dynamic_cast<prf::vulkan::Profiler*>(profiler)){
          this->selected_profiler = gui_vulkan;
          gui_vulkan->draw_profiler(vulkan);
        }
        //Hardware tab
        else if(prf::hardware::Profiler* temperature = dynamic_cast<prf::hardware::Profiler*>(profiler)){
          this->selected_profiler = gui_hardware;
          gui_hardware->draw_profiler(temperature);
        }

        ImGui::EndTabItem();
      }
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}

}
