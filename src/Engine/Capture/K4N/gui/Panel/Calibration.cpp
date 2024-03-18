#include "Calibration.h"

#include <K4N/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Calibration::Calibration(k4n::Node* node_k4n, bool* show_window){
  //---------------------------

  this->k4n_hough = new k4n::utils::Hough();

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

  this->hough_parameter();

  //---------------------------
}

//Subfunction
void Calibration::hough_parameter(){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Hough parameter");

  //Canny
  bool* apply_canny = k4n_hough->get_apply_canny();
  ImGui::Checkbox("Canny", apply_canny);

  if(*apply_canny){
    ImGui::Indent();

    //Lower threshold
    float* threshold_lower = k4n_hough->get_canny_thres_lower();
    ImGui::SetNextItemWidth(125);
    ImGui::SliderFloat("Lower threshold", threshold_lower, 1.0f, 200.0f);

    //Upper threshold
    float* threshold_upper = k4n_hough->get_canny_thres_upper();
    ImGui::SetNextItemWidth(125);
    ImGui::SliderFloat("Upper threshold", threshold_upper, 1.0f, 200.0f);

    ImGui::Unindent();
  }

  //Mode
  int* mode = k4n_hough->get_mode();
  ImGui::RadioButton("Gradient", mode, k4n::hough::GRADIENT);
  ImGui::SameLine();
  ImGui::RadioButton("Standard", mode, k4n::hough::STANDARD);
  ImGui::SameLine();
  ImGui::RadioButton("Probabilistic", mode, k4n::hough::PROBABILISTIC);

  //Ratio
  int* ratio = k4n_hough->get_ratio();
  ImGui::SetNextItemWidth(150);
  ImGui::SliderInt("Ratio", ratio, 1, 100);

  //Min distance
  float* min_dist = k4n_hough->get_min_dist();
  ImGui::SetNextItemWidth(150);
  ImGui::SliderFloat("Min distance", min_dist, 0.0f, 5.0f);

  //Min radius
  float* min_radius = k4n_hough->get_min_radius();
  ImGui::SetNextItemWidth(150);
  ImGui::SliderFloat("Min radius", min_radius, 0.0f, 5.0f);

  //Max radius
  float* max_radius = k4n_hough->get_max_radius();
  ImGui::SetNextItemWidth(150);
  ImGui::SliderFloat("Max radius", max_radius, 0.0f, 5.0f);

  //---------------------------
}


}
