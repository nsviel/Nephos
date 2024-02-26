#include "Graph.h"

#include <Engine/Namespace.h>
#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>


namespace prf::gui{

//Constructor / Destructor
Graph::Graph(prf::Node* node_profiler){
  //---------------------------

  this->prf_manager = node_profiler->get_prf_manager();

  //---------------------------
}
Graph::~Graph(){}

//Main function
void Graph::draw_profiler(prf::graph::Profiler* profiler){
  //---------------------------

  if(ImGui::BeginTabBar("tasker_gui##4567")){
    this->draw_graph_all(profiler);
    this->draw_graph_unique(profiler);

    ImGui::EndTabBar();
  }

  //---------------------------
}

//Subfunction
void Graph::draw_graph_all(prf::graph::Profiler* profiler){
  ImVec2 graph_dim = ImGui::GetContentRegionAvail();
  //---------------------------

  //Find not empty taskers
  vector<prf::graph::Tasker*> vec_tasker = profiler->get_vec_tasker();
  vector<prf::graph::Tasker*> vec_tasker_not_empty;
  for(int i=0; i<vec_tasker.size(); i++){
    prf::graph::Tasker* tasker = vec_tasker[i];

    if(!tasker->is_empty()){
      vec_tasker_not_empty.push_back(tasker);
    }
  }
  if(vec_tasker_not_empty.size() < 2) return;

  //Stuff to force first-opened tab
  static bool first_tab_open = true;
  ImGuiTabItemFlags flag = 0;
  if(first_tab_open){
    flag = ImGuiTabItemFlags_SetSelected;
    first_tab_open = false;
  }

  //All not empty tasker graphs
  ImGui::SetNextItemWidth(100);
  if(ImGui::BeginTabItem("All##4568", NULL, flag)){
    prf::graph::Profiler* profiler = prf_manager->get_profiler_main();
    this->selected_tasker = profiler->get_tasker("cpu");
    graph_dim = ImVec2(graph_dim.x, graph_dim.y/vec_tasker_not_empty.size() - 3);

    for(int i=0; i<vec_tasker_not_empty.size(); i++){
      this->draw_tasker_graph(vec_tasker_not_empty[i], graph_dim);
    }
    ImGui::EndTabItem();
  }

  //---------------------------
}
void Graph::draw_graph_unique(prf::graph::Profiler* profiler){
  ImVec2 graph_dim = ImGui::GetContentRegionAvail();
  //---------------------------

  vector<prf::graph::Tasker*> vec_tasker = profiler->get_vec_tasker();
  for(int i=0; i<vec_tasker.size(); i++){
    prf::graph::Tasker* tasker = vec_tasker[i];

    //Improfil graphs
    ImGui::SetNextItemWidth(100);
    string title = tasker->get_name() + "##45454";
    if(!tasker->is_empty() && ImGui::BeginTabItem(title.c_str(), NULL)){
      this->selected_tasker = tasker;
      this->draw_tasker_graph(tasker, graph_dim);
      ImGui::EndTabItem();
    }
  }

  //---------------------------
}
void Graph::draw_tasker_graph(prf::graph::Tasker* tasker, ImVec2 graph_dim){
  prf::improfil::Manager* gui_graph = tasker->get_gui_graph();
  //---------------------------

  if(!pause){
    //Reset graph
    gui_graph->reset();

    //Assign tasks
    vector<prf::graph::Task>& vec_task = tasker->get_vec_task();
    for(int i=0; i<vec_task.size(); i++){
      prf::graph::Task task = vec_task[i];

      if(task.color == vec4(0, 0, 0, 0)){
        gui_graph->add_task(task.time_beg, task.time_end, task.name);
      }else{
        gui_graph->add_task(task.time_beg, task.time_end, task.name, task.color);
      }
    }

    //load data
    gui_graph->load_data_to_graph();
  }

  //Render profiler
  gui_graph->render_child(graph_dim);

  //---------------------------
}

}
