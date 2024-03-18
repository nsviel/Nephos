#include "Calibration.h"

#include <K4N/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Calibration::Calibration(k4n::Node* node_k4n, bool* show_window){
  //---------------------------

  this->show_window = show_window;
  this->name = "Calibration";

  //---------------------------
}
Calibration::~Calibration(){}

//Main function
void Calibration::run_panel(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(100, 400), ImVec2(FLT_MAX, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Calibration::design_panel(){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Hough parameter");

  //---------------------------
}


}
