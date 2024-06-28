#include "Graph.h"

#include <Engine/Namespace.h>
#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace prf::gui::dynamic{

//Constructor / Destructor
Graph::Graph(prf::Node* node_profiler){
  //---------------------------

  this->prf_struct = node_profiler->get_prf_struct();

  //---------------------------
}
Graph::~Graph(){}

//Main function
void Graph::draw_profiler(prf::dynamic::Profiler* profiler){
  //---------------------------

  this->draw_info();

  if(ImGui::BeginTabBar("profiler_tasker_tab")){

    this->draw_tasker_all(profiler);
    this->draw_tasker_separated(profiler);

    ImGui::EndTabBar();
  }

  //---------------------------
}

//Graph function
void Graph::draw_info(){
  if(current_tasker == nullptr) return;
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  ImGui::BeginTable("info##profiler_dynamic", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);

  //Thread
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Thread"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", current_tasker->thread_ID.c_str());

  //FPS
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Loop"); ImGui::TableNextColumn();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", 1000.0f / current_tasker->fps);
  ImGui::SameLine();
  ImGui::Text(" ms/frame [");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", current_tasker->fps); //io.Framerate
  ImGui::SameLine();
  ImGui::Text(" FPS ]");

  ImGui::EndTable();

  //---------------------------
}
void Graph::draw_tasker_all(prf::dynamic::Profiler* profiler){
  std::list<prf::dynamic::Tasker*> list_tasker = profiler->get_list_tasker();
  //---------------------------

  //Stuff to force first-opened tab
  static bool first_tab_open = true;
  ImGuiTabItemFlags flag = 0;
  if(first_tab_open){
    flag = ImGuiTabItemFlags_SetSelected;
    first_tab_open = false;
  }

  //All not empty tasker graphs*/
  ImVec2 dimension = ImGui::GetContentRegionAvail();
  ImGui::SetNextItemWidth(dimension.x / (list_tasker.size() + 1));
  std::string title = "All##" + profiler->name;
  if(ImGui::BeginTabItem(title.c_str(), NULL, 0)){

    //Command + plot
    ImGui::BeginTable(title.c_str(), 2);
    ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 17.5);
    ImGui::TableSetupColumn("2", ImGuiTableColumnFlags_WidthStretch);

    //Graph command
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    this->draw_graph_command();

    //Graph plots
    ImGui::TableNextColumn();
    ImVec2 dim_plot = ImVec2(dimension.x, dimension.y / list_tasker.size() - list_tasker.size() * 4);
    for(int i=0; i<list_tasker.size(); i++){
      prf::dynamic::Tasker* tasker = *next(list_tasker.begin(), i);
      this->draw_tasker_graph(tasker, dim_plot);
    }

    ImGui::EndTable();

    ImGui::EndTabItem();
  }

  //---------------------------
}
void Graph::draw_tasker_separated(prf::dynamic::Profiler* profiler){
  ImVec2 dimension = ImGui::GetContentRegionAvail();
  dimension = ImVec2(dimension.x, dimension.y - 10);
  //---------------------------

  std::list<prf::dynamic::Tasker*> list_tasker = profiler->get_list_tasker();
  for(int i=0; i<list_tasker.size(); i++){
    prf::dynamic::Tasker* tasker = *next(list_tasker.begin(), i);

    ImGui::SetNextItemWidth(dimension.x / (list_tasker.size() + 1));
    std::string title = tasker->name + "##" + tasker->thread_ID;
    if(ImGui::BeginTabItem(title.c_str(), NULL)){
      ImGui::BeginTable(title.c_str(), 2);
      ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 17.5);
      ImGui::TableSetupColumn("2", ImGuiTableColumnFlags_WidthStretch);

      //Graph command
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      this->draw_graph_command();

      //Graph plot
      ImGui::TableNextColumn();
      this->draw_tasker_graph(tasker, dimension);

      ImGui::EndTable();
      ImGui::EndTabItem();
    }
  }

  //---------------------------
}

//Subfunction
void Graph::draw_graph_command(){
  //---------------------------

  //Play / pause button
  if(prf_struct->dynamic.pause){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, 255));
    if(ImGui::Button(ICON_FA_PLAY "##profiler_play", ImVec2(20, 0))){
      prf_struct->dynamic.pause = false;
    }
    ImGui::PopStyleColor();
  }
  else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(45, 133, 133, 255));
    if(ImGui::Button(ICON_FA_PAUSE "##profiler_pause")){
      prf_struct->dynamic.pause = true;
    }
    ImGui::PopStyleColor();
  }

  //Max visible ms
  ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
  ImGui::VSliderInt("Y axis", ImVec2(22, ImGui::GetContentRegionAvail().y), &prf_struct->dynamic.max_time, 100, 10, "%d");
  ImGui::PopStyleColor(5);

  //---------------------------
}
void Graph::draw_tasker_graph(prf::dynamic::Tasker* tasker, ImVec2 dimension){
  //---------------------------

  this->current_tasker = tasker;

  //Update plot
  if(!prf_struct->dynamic.pause){
    tasker->update();
  }

  //Render plot
  tasker->plot.set_time_max(prf_struct->dynamic.max_time);
  tasker->plot.render(tasker->name, dimension);

  //---------------------------
}

}
