#include "Panel.h"

#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <Dynamic/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace ldr::gui::exporter{

//Constructor / Destructor
Panel::Panel(ldr::Node* node_loader, bool* show_window){
  //---------------------------

  dat::Node* node_data = node_loader->get_node_data();

  this->ldr_struct = node_loader->get_ldr_struct();
  this->dat_selection = node_data->get_dat_selection();
  this->ldr_exporter = node_loader->get_ldr_exporter();
  this->gui_navigator = new utl::gui::Navigator();
  this->gui_exporter = new ldr::gui::exporter::Exporter(node_loader);
  this->gui_recorder = new ldr::gui::exporter::Recorder(node_loader);

  this->name = "Export##555";
  this->show_window = show_window;

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  if(*show_window && element != nullptr){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(400, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

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
  if(ldr_exporter->is_recording(element)){
    gui_recorder->draw_header(element);
  }
  //Exporter
  else{
    gui_exporter->draw_header(element);
  }

  //Navigator
  ldr_exporter->update_current_path(element);
  gui_navigator->draw_navigator(ldr_struct->exporter.path);

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
    gui_recorder->item_operation();
  }
  //Else, it's static object
  else{
    gui_exporter->item_operation();
  }

  //---------------------------
}

}
