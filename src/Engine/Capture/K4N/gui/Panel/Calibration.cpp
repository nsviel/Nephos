#include "Calibration.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <K4N/Namespace.h>
#include <Scene/Namespace.h>
#include <Render/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Calibration::Calibration(k4n::Node* node_k4n, bool* show_window){
  //---------------------------

  //---------------------------
}
Calibration::~Calibration(){}

//Main function
void Calibration::run_panel(){
  k4n::dev::Master* master = k4n_swarm->get_selected_master();
  //---------------------------

  if(*show_window && master != nullptr && k4n_swarm->get_number_running_thread() != 0){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(100, 400), ImVec2(FLT_MAX, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel(master);

      ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Calibration::design_panel(k4n::dev::Master* master){
  //---------------------------



  //---------------------------
}


}
