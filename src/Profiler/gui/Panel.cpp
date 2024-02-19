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
  this->prf_vulkan = node_profiler->get_prf_vulkan();

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
  this->draw_graph();

  //---------------------------
}

//Subfunction
void Panel::main_info(){
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  if(ImGui::BeginTable("render##device", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);

    //GPU device
    prf::vulkan::Info* info_vulkan = prf_vulkan->get_info_vulkan();
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Device"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", info_vulkan->selected_gpu.c_str());
/*
    //Main loop fps
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Loop"); ImGui::TableNextColumn();
    ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", 1000.0f / tasker_cpu->get_loop_fps());
    ImGui::SameLine();
    ImGui::Text(" ms/frame [");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%.1f", tasker_cpu->get_loop_fps()); //io.Framerate
    ImGui::SameLine();
    ImGui::Text(" FPS ]");
*/
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
void Panel::draw_graph(){
  //---------------------------

  if(ImGui::BeginTabBar("device_tab##4567")){
    this->draw_graph_all();
    this->draw_graph_unique();
    this->draw_graph_vulkan();

    ImGui::EndTabBar();
  }

  //---------------------------
}
void Panel::draw_graph_all(){
  ImVec2 graph_dim = ImGui::GetContentRegionAvail();
  //---------------------------

  //Find not empty taskers
  vector<prf::Tasker*> vec_tasker = prf_manager->get_vec_tasker();
  vector<prf::Tasker*> vec_tasker_not_empty;
  for(int i=0; i<vec_tasker.size(); i++){
    if(!vec_tasker[i]->is_empty()){
      vec_tasker_not_empty.push_back(vec_tasker[i]);
    }
  }

  //All not empty tasker graphs
  ImGui::SetNextItemWidth(100);
  if(vec_tasker_not_empty.size() > 1 && ImGui::BeginTabItem("All##4568", NULL)){
    graph_dim = ImVec2(graph_dim.x, graph_dim.y/vec_tasker_not_empty.size() - 3);

    for(int i=0; i<vec_tasker_not_empty.size(); i++){
      this->draw_tasker_graph(vec_tasker_not_empty[i], graph_dim);
    }
    ImGui::EndTabItem();
  }

  //---------------------------
}
void Panel::draw_graph_unique(){
  ImVec2 graph_dim = ImGui::GetContentRegionAvail();
  //---------------------------

  vector<prf::Tasker*> vec_tasker = prf_manager->get_vec_tasker();
  for(int i=0; i<vec_tasker.size(); i++){
    prf::Tasker* tasker = vec_tasker[i];

    ImGui::SetNextItemWidth(100);
    string title = tasker->get_name() + "##45454";
    if (ImGui::BeginTabItem(title.c_str(), NULL)){
      this->draw_tasker_graph(tasker, graph_dim);
      ImGui::EndTabItem();
    }
  }

  //---------------------------
}
void Panel::draw_graph_vulkan(){
  ImVec2 graph_dim = ImGui::GetContentRegionAvail();
  //---------------------------

  ImGui::SetNextItemWidth(100);
  if (ImGui::BeginTabItem("Vulkan##4567", NULL)){
    this->draw_profiler_vulkan(graph_dim);
    ImGui::EndTabItem();
  }

  //---------------------------
}

//Profiler graphs
void Panel::draw_tasker_graph(prf::Tasker* tasker, ImVec2 graph_dim){
  prf::improfil::Manager* gui_graph = tasker->get_gui_graph();
  //---------------------------

  if(!pause){
    //Reset graph
    gui_graph->reset();

    //Assign tasks
    vector<prf::type::Task>& vec_task = tasker->get_vec_task();
    for(int i=0; i<vec_task.size(); i++){
      prf::type::Task task = vec_task[i];

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
void Panel::draw_profiler_vulkan(ImVec2 graph_dim){
  vector<prf::vulkan::Device>& vec_device = prf_vulkan->get_info_device();
  //---------------------------

  ImVec4 color = ImVec4(0.5, 1, 0.5, 1);
  if(ImGui::BeginTabBar("vulkan_profiler_tab##4567")){
    for(int i=0; i< vec_device.size(); i++){
      prf::vulkan::Device& device = vec_device[i];

      if(ImGui::BeginTabItem(device.name.c_str(), NULL)){

        if(ImGui::BeginTable("vulkan_device##profiler", 2)){
          ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthStretch, 75.0f);

          //GPU name
          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("Name"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%s", device.name.c_str());

          //Vendor ID
          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("Vendor ID"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.vendorID);

          //Extension support
          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("Extension support"); ImGui::TableNextColumn();
          const char* support = device.has_extension_support ? "true" : "false";
          ImGui::TextColored(color, "%s", support);

          //Max image
          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("Max image"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.max_image_dim);

          //Queue stuff
          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("Queue graphics ID"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.queue_family_graphics_idx);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("Queue transfer ID"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.queue_family_transfer_idx);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("Queue presentation ID"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.queue_family_presentation_idx);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("No family queues"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.nb_queue_family);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("No graphics queues"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.nb_queue_graphics);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("No compute queues"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.nb_queue_compute);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("No transfer queues"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.nb_queue_transfer);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("No sparse binding queues"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.nb_queue_sparseBinding);

          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("No presentation queues"); ImGui::TableNextColumn();
          ImGui::TextColored(color, "%d", device.nb_queue_presentation);

          ImGui::EndTable();
        }

        ImGui::EndTabItem();
      }

    }
    ImGui::EndTabBar();
  }

  //---------------------------
}
void Panel::set_graphs_max_time(int& value){
  vector<prf::Tasker*> vec_tasker = prf_manager->get_vec_tasker();
  //---------------------------

  for(int i=0; i<vec_tasker.size(); i++){
    prf::Tasker* tasker = vec_tasker[i];
    prf::improfil::Manager* gui_graph = tasker->get_gui_graph();

    gui_graph->set_time_max(max_time);
  }

  //---------------------------
}

}
