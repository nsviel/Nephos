#include "Graph.h"

#include <Engine/Namespace.h>
#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>


namespace prf::gui{

//Constructor / Destructor
Graph::Graph(prf::Node* node_profiler){
  //---------------------------

  this->prf_manager = node_profiler->get_prf_manager();
  this->pause = false;

  //---------------------------
}
Graph::~Graph(){}

//Main function
void Graph::show_info(){
  if(selected_tasker == nullptr) return;
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);

  //Thread
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Thread"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", selected_tasker->thread_ID.c_str());

  //FPS
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Loop"); ImGui::TableNextColumn();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", 1000.0f / selected_tasker->fps);
  ImGui::SameLine();
  ImGui::Text(" ms/frame [");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", selected_tasker->fps); //io.Framerate
  ImGui::SameLine();
  ImGui::Text(" FPS ]");

  //---------------------------
}
void Graph::show_profiler(prf::base::Profiler* profiler){
  prf::graph::Profiler* graph = dynamic_cast<prf::graph::Profiler*>(profiler);
  //---------------------------

  if(ImGui::BeginTabBar("tasker_gui##4567")){
    ImVec2 graph_dim = ImGui::GetContentRegionAvail();

    this->draw_graph_all(graph);
    this->draw_graph_unique(graph);

    ImGui::EndTabBar();
  }

  //---------------------------
}

//Graph function
void Graph::draw_graph_all(prf::graph::Profiler* profiler){
  //---------------------------

  //Find not empty taskers
  std::list<prf::graph::Tasker*> list_tasker = profiler->get_list_tasker();
  std::vector<prf::graph::Tasker*> vec_tasker;
  for(int i=0; i<list_tasker.size(); i++){
    prf::graph::Tasker* tasker = *next(list_tasker.begin(), i);

    if(!tasker->vec_task.empty()){
      vec_tasker.push_back(tasker);
    }
  }
  if(vec_tasker.size() < 2) return;

  //Stuff to force first-opened tab
  static bool first_tab_open = true;
  ImGuiTabItemFlags flag = 0;
  if(first_tab_open){
    flag = ImGuiTabItemFlags_SetSelected;
    first_tab_open = false;
  }

  //All not empty tasker graphs
  ImVec2 graph_dim = ImGui::GetContentRegionAvail();
  ImGui::SetNextItemWidth(graph_dim.x / (list_tasker.size() + 1));
  string title = "All##" + profiler->name;
  if(ImGui::BeginTabItem("All##4568", NULL, flag)){

    ImGui::BeginTable(title.c_str(), 2);
    ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 17.5);
    ImGui::TableSetupColumn("2", ImGuiTableColumnFlags_WidthStretch);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    this->draw_graph_command();

    ImGui::TableNextColumn();

    graph_dim = ImVec2(graph_dim.x, graph_dim.y / vec_tasker.size() - 3);

    for(int i=0; i<vec_tasker.size(); i++){
      this->draw_tasker_graph(vec_tasker[i], graph_dim);
    }

    ImGui::EndTable();

    ImGui::EndTabItem();
  }

  //---------------------------
}
void Graph::draw_graph_unique(prf::graph::Profiler* profiler){
  //---------------------------

  std::list<prf::graph::Tasker*> list_tasker = profiler->get_list_tasker();
  for(int i=0; i<list_tasker.size(); i++){
    prf::graph::Tasker* tasker = *next(list_tasker.begin(), i);

    //Improfil graphs
    ImVec2 graph_dim = ImGui::GetContentRegionAvail();
    ImGui::SetNextItemWidth(graph_dim.x / (list_tasker.size() + 1));
    string title = tasker->name + "##" + tasker->thread_ID;
    if(!tasker->vec_task.empty() && ImGui::BeginTabItem(title.c_str(), NULL)){

      ImGui::BeginTable(title.c_str(), 2);
      ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 17.5);
      ImGui::TableSetupColumn("2", ImGuiTableColumnFlags_WidthStretch);

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      this->draw_graph_command();

      ImGui::TableNextColumn();
      this->draw_tasker_graph(tasker, graph_dim);

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
  if(pause){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, 255));
    if(ImGui::Button(ICON_FA_PLAY "##profiler_play", ImVec2(20, 0))){
      pause = false;
    }
    ImGui::PopStyleColor();
  }
  else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(45, 133, 133, 255));
    if(ImGui::Button(ICON_FA_PAUSE "##profiler_pause")){
      pause = true;
    }
    ImGui::PopStyleColor();
  }

  //Max visible ms
  ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
  if(ImGui::VSliderInt("Y axis", ImVec2(22, ImGui::GetContentRegionAvail().y), &max_time, 100, 10, "%d")){
    this->set_graphs_max_time(max_time);
  }
  ImGui::PopStyleColor(2);
  ImGui::PopStyleVar(5);

  //---------------------------
}
void Graph::draw_tasker_graph(prf::graph::Tasker* tasker, ImVec2 graph_dim){
  //---------------------------

  this->selected_tasker = tasker;

  if(!pause){
    //Reset graph
    tasker->graph.reset();

    //Assign tasks


    for(int i=0; i<tasker->vec_task.size(); i++){
      prf::graph::structure::Task task = tasker->vec_task[i];

      if(task.color == vec4(0, 0, 0, 0)){
        tasker->graph.add_task(task.ts_begin, task.ts_end, task.name);
      }else{
        tasker->graph.add_task(task.ts_begin, task.ts_end, task.name, task.color);
      }
    }

    //load data
    tasker->graph.load_data_to_graph();
  }

  //Render profiler
  tasker->graph.render_child(graph_dim);

  //---------------------------
}
void Graph::set_graphs_max_time(int value){
  std::list<prf::base::Profiler*> list_profiler = prf_manager->get_list_profiler();
  //---------------------------

  for(int i=0; i<list_profiler.size(); i++){
    prf::base::Profiler* profiler = *next(list_profiler.begin(), i);

    if(prf::graph::Profiler* graph = dynamic_cast<prf::graph::Profiler*>(profiler)){
      list<prf::graph::Tasker*> list_tasker = graph->get_list_tasker();

      for(int i=0; i<list_tasker.size(); i++){
        prf::graph::Tasker* tasker = *next(list_tasker.begin(), i);

        tasker->graph.set_time_max(value);
      }
    }
  }

  //---------------------------
}

}
