#include "Panel.h"

#include <Exporter/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace io::exp::gui{

//Constructor / Destructor
Panel::Panel(io::exp::Node* node_exporter, bool* show_window){
  //---------------------------

  dat::Node* node_data = node_exporter->get_node_data();
  dat::graph::Node* node_graph = node_data->get_node_graph();

  this->io_struct = node_exporter->get_io_struct();
  this->dat_selection = node_graph->get_dat_selection();
  this->io_exporter = node_exporter->get_io_exporter();
  this->gui_navigator = new utl::gui::Navigator();
  this->gui_exporter = new io::exp::gui::Exporter(node_exporter);
  this->gui_recorder = new io::exp::gui::Recorder(node_exporter);

  this->name = "Export##555";
  this->show_window = show_window;

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  utl::base::Element* element = dat_selection->get_selected_element();
  if(element == nullptr) return;
  //---------------------------

  if(*show_window){
    ImGuiWindowFlags flag;
    flag |= ImGuiWindowFlags_NoCollapse;
    flag |= ImGuiWindowFlags_AlwaysAutoResize;
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(400, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, flag) == 1){

      this->design_panel(element);

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(utl::base::Element* element){
  //---------------------------

  //Recorder
  if(io_exporter->is_recording(element)){
    gui_recorder->draw_header(element);
  }
  //Exporter
  else{
    gui_exporter->draw_header(element);
  }

  //Navigator
  io_exporter->update_current_path(element);
  gui_navigator->draw_navigator(io_struct->path);

  //---------------------------
  ImGui::Separator();
}

//Navigator function
void Panel::item_filtering(std::vector<std::string>& vec_path){
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  if(entity == nullptr) return;
  //---------------------------

  //If dynamic object
  dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity);
  if(sensor && sensor->vec_recorder.size() != 0){
    gui_recorder->item_filtering(vec_path);
  }
  //Else, it's static object
  else{
    gui_exporter->item_filtering(vec_path);
  }

  //---------------------------
}
void Panel::item_operation(){
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  if(entity == nullptr) return;
  //---------------------------

  //If dynamic object
  if(dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity)){
    gui_recorder->item_operation(entity);
  }
  //Else, it's static object
  else{
    gui_exporter->item_operation(entity);
  }

  //---------------------------
}

}
