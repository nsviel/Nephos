#include "Graph.h"

#include <Engine/Namespace.h>
#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>
#include <imgui/core/imgui.h>


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
  if(list_tasker.size() < 2) return;
  //---------------------------

  //Stuff to force first-opened tab
  static bool first_tab_open = true;
  ImGuiTabItemFlags flag = 0;
  if(first_tab_open){
    flag = ImGuiTabItemFlags_SetSelected;
    first_tab_open = false;
    this->current_tasker = *next(list_tasker.begin(), 0);
  }

  //Tasker tabs
  std::string title = "All##" + profiler->name;
  int width = ImGui::GetContentRegionAvail().x / (list_tasker.size() + 1);
  ImGui::SetNextItemWidth(width);
  ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
  if(ImGui::BeginTabItem(title.c_str(), NULL, flag)){
    ImVec2 image_pose = ImGui::GetCursorScreenPos();
    ImVec2 dim = ImGui::GetContentRegionAvail();

    //Child
    ImGui::BeginChild("child##tasker_plot", ImVec2(0, 0), false);

    //Graph plots
    dim = ImGui::GetContentRegionAvail();
    ImVec2 dimension = ImVec2(dim.x, dim.y / list_tasker.size());
    for(int i=0; i<list_tasker.size(); i++){
      prf::dynamic::Tasker* tasker = *next(list_tasker.begin(), i);
      if(!tasker->is_idle()){
        //this->draw_tasker_graph(tasker, dimension, profiler->pause);
      }
    }

    ImGui::EndChild();

    //Graph command
    ImGuiWindowFlags flags;
    flags |= ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_AlwaysAutoResize;
    flags |= ImGuiWindowFlags_NoSavedSettings;
    flags |= ImGuiWindowFlags_NoFocusOnAppearing;
    flags |= ImGuiWindowFlags_NoDecoration;
    flags |= ImGuiWindowFlags_NoDocking;
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::SetNextWindowPos(image_pose, ImGuiCond_Always);
    ImGui::Begin("kzehfdize#hell", nullptr, flags);
    this->draw_graph_command(dim);
    ImGui::End();

    ImGui::EndTabItem();
  }
  ImGui::PopStyleVar(2);

  //---------------------------
}
void Graph::draw_tasker_separated(prf::dynamic::Profiler* profiler){
  //---------------------------

  std::list<prf::dynamic::Tasker*> list_tasker = profiler->get_list_tasker();
  for(int i=0; i<list_tasker.size(); i++){
    prf::dynamic::Tasker* tasker = *next(list_tasker.begin(), i);

    //Tasker tab
    std::string title = tasker->name + "##tasker_unique_plot";
    int width = ImGui::GetContentRegionAvail().x / (list_tasker.size() + 1);
    ImGui::SetNextItemWidth(width);
    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

    if(ImGui::BeginTabItem(title.c_str(), NULL)){
      ImVec2 image_pose = ImGui::GetCursorScreenPos();
      ImVec2 dim = ImGui::GetContentRegionAvail();

      //Child
      ImGui::BeginChild("child##tasker_plot", ImVec2(0, 0), false);

      //Graph plot
      this->current_tasker = tasker;
      this->draw_tasker_graph(tasker, dim, profiler->pause);

      ImGui::EndChild();

      //Graph command
      ImGuiWindowFlags flags;
      flags |= ImGuiWindowFlags_NoMove;
      flags |= ImGuiWindowFlags_AlwaysAutoResize;
      flags |= ImGuiWindowFlags_NoSavedSettings;
      flags |= ImGuiWindowFlags_NoFocusOnAppearing;
      flags |= ImGuiWindowFlags_NoDecoration;
      flags |= ImGuiWindowFlags_NoDocking;
      ImGui::SetNextWindowBgAlpha(0.0f);
      ImGui::SetNextWindowPos(image_pose, ImGuiCond_Always);
      ImGui::Begin("kzehfdize#hell", nullptr, flags);

      this->draw_graph_command(dim);

      ImGui::End();

      ImGui::EndTabItem();
    }

    ImGui::PopStyleVar(2);
  }

  //---------------------------
}

//Subfunction
void Graph::draw_graph_command(ImVec2 dimension){
  //---------------------------

  //Play / pause button
  if(prf_struct->dynamic.pause){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, 255));
    if(ImGui::Button(ICON_FA_PLAY "##profiler_play")){
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
  ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
  ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.2f));
  ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.0f, 0.0f, 0.0f, 0.2f));
  ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));



  ImGui::VSliderInt("##Y_axis", ImVec2(24, dimension.y), &prf_struct->dynamic.max_time, 100, 10, "%d");
  ImGui::PopStyleColor(6);

  //---------------------------
}
void Graph::draw_tasker_graph(prf::dynamic::Tasker* tasker, ImVec2 dimension, bool pause){
  //---------------------------

  //Update plot
  if(!prf_struct->dynamic.pause && !pause){
    tasker->update();
  }

  //Render plot
  tasker->plot.set_time_max(prf_struct->dynamic.max_time);
  tasker->plot.render(tasker->name, dimension);

  //---------------------------
}

}
