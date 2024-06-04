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
void Graph::draw_profiler(prf::graph::Profiler* profiler){
  //---------------------------

  if(ImGui::BeginTabBar("tasker_gui##4567")){
    this->draw_graph_all(profiler);
    this->draw_graph_unique(profiler);

    ImGui::EndTabBar();
  }

  //---------------------------
}
void Graph::show_info(){
  if(selected_tasker == nullptr) return;
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);

  //Thread
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Thread"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", selected_tasker->get_thread_ID().c_str());

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

  //---------------------------
}

//Subfunction
void Graph::draw_graph_all(prf::graph::Profiler* profiler){
  ImVec2 graph_dim = ImGui::GetContentRegionAvail();
  //---------------------------

  //Find not empty taskers
  list<prf::graph::Tasker*> list_tasker = profiler->get_list_tasker();
  vector<prf::graph::Tasker*> vec_tasker;

  for(int i=0; i<list_tasker.size(); i++){
    prf::graph::Tasker* tasker = *next(list_tasker.begin(), i);

    if(!tasker->is_empty()){
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
  ImGui::SetNextItemWidth(100);
  if(ImGui::BeginTabItem("All##4568", NULL, flag)){
    prf::graph::Profiler* profiler = prf_manager->get_profiler_main();
    graph_dim = ImVec2(graph_dim.x, graph_dim.y/vec_tasker.size() - 3);

    for(int i=0; i<vec_tasker.size(); i++){
      this->draw_tasker_graph(vec_tasker[i], graph_dim);
    }
    ImGui::EndTabItem();
  }

  //---------------------------
}
void Graph::draw_graph_unique(prf::graph::Profiler* profiler){
  ImVec2 graph_dim = ImGui::GetContentRegionAvail();
  //---------------------------

  list<prf::graph::Tasker*> list_tasker = profiler->get_list_tasker();
  for(int i=0; i<list_tasker.size(); i++){
    prf::graph::Tasker* tasker = *next(list_tasker.begin(), i);

    //Improfil graphs
    ImGui::SetNextItemWidth(100);
    string title = tasker->get_name() + "##45454";
    if(!tasker->is_empty() && ImGui::BeginTabItem(title.c_str(), NULL)){
      this->draw_tasker_graph(tasker, graph_dim);
      ImGui::EndTabItem();
    }
  }

  //---------------------------
}
void Graph::draw_tasker_graph(prf::graph::Tasker* tasker, ImVec2 graph_dim){
  prf::improfil::Manager* gui_graph = tasker->get_gui_graph();
  //---------------------------

  this->selected_tasker = tasker;

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
void Graph::set_graphs_max_time(int value){
  std::list<prf::Structure*> list_profiler = prf_manager->get_list_profiler();
  //---------------------------

  for(int i=0; i<list_profiler.size(); i++){
    prf::Structure* profiler = *next(list_profiler.begin(), i);

    if(prf::graph::Profiler* graph = dynamic_cast<prf::graph::Profiler*>(profiler)){
      list<prf::graph::Tasker*> list_tasker = graph->get_list_tasker();

      for(int i=0; i<list_tasker.size(); i++){
        prf::graph::Tasker* tasker = *next(list_tasker.begin(), i);
        prf::improfil::Manager* gui_graph = tasker->get_gui_graph();

        gui_graph->set_time_max(value);
      }
    }
  }

  //---------------------------
}

}
