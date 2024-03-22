#include "Matching.h"

#include <K4N/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Matching::Matching(k4n::Node* node_k4n, bool* show_window){
  //---------------------------

  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->k4n_struct = node_k4n->get_k4n_struct();
  this->gui_detection = new k4n::gui::Detection(node_k4n);
  this->gui_calibration = new k4n::gui::Calibration(node_k4n);

  this->show_window = show_window;
  this->name = "Matching";

  //---------------------------
}
Matching::~Matching(){}

//Main function
void Matching::run_panel(){
  k4n::dev::Master* master = k4n_swarm->get_selected_master();
  //---------------------------

  if(*show_window && master != nullptr){
    k4n_struct->matching.panel_open = true;

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(100, 400), ImVec2(FLT_MAX, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel(master);

      ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
  }else{
    k4n_struct->matching.panel_open = false;
  }

  //---------------------------
}
void Matching::design_panel(k4n::dev::Master* master){
  k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(master->selected_entity);
  //---------------------------

  gui_detection->draw_detection(sensor);
  gui_calibration->draw_calibration(sensor);

  //---------------------------
}

//Subfunction
void Matching::tab_detection(k4n::dev::Sensor* sensor){
  //---------------------------

  gui_detection->draw_detection(sensor);

  //---------------------------
}
void Matching::tab_calibration(k4n::dev::Sensor* sensor){
  //---------------------------

  gui_calibration->draw_calibration(sensor);

  //---------------------------
}
void Matching::tab_registration(k4n::dev::Sensor* sensor){
  //---------------------------



  //---------------------------
}

}
