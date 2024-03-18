#include "Calibration.h"

#include <K4N/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Calibration::Calibration(k4n::Node* node_k4n, bool* show_window){
  //---------------------------

  this->k4n_hough = new k4n::utils::Hough();
  this->k4n_model = node_k4n->get_k4n_model();

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

  this->model_parameter();
  this->hough_parameter();

  //---------------------------
}

//Subfunction
void Calibration::model_parameter(){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Model parameter");

  //Max radius
  float* sphere_diameter = k4n_model->get_sphere_diameter();
  ImGui::SetNextItemWidth(150);
  ImGui::SliderFloat("Sphere diameter", sphere_diameter, 1.0f, 50.0f, "%.1f");

  //---------------------------
  ImGui::Separator();
}
void Calibration::hough_parameter(){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Hough parameter");

  //Canny
  bool* apply_canny = k4n_hough->get_apply_canny();
  ImGui::Checkbox("Canny", apply_canny);

  if(*apply_canny){
    ImGui::Indent();

    //Lower threshold
    int* threshold_lower = k4n_hough->get_canny_thres_lower();
    ImGui::SetNextItemWidth(125);
    ImGui::SliderInt("Lower threshold", threshold_lower, 0, 200);

    //Upper threshold
    int* threshold_upper = k4n_hough->get_canny_thres_upper();
    ImGui::SetNextItemWidth(125);
    ImGui::SliderInt("Upper threshold", threshold_upper, 0, 200);

    ImGui::Unindent();
  }

  //Mode
  int* mode = k4n_hough->get_mode();
  ImGui::RadioButton("Gradient", mode, k4n::hough::GRADIENT);
  ImGui::SameLine();
  ImGui::RadioButton("Standard", mode, k4n::hough::STANDARD);
  ImGui::SameLine();
  ImGui::RadioButton("Probabilistic", mode, k4n::hough::PROBABILISTIC);

  {
    ImGui::Indent();

    //Lower threshold
    float* param_1 = k4n_hough->get_param_1();
    ImGui::SetNextItemWidth(125);
    ImGui::SliderFloat("Parameter 1", param_1, 1.0f, 100.0f, "%.1f");

    //Upper threshold
    float* param_2 = k4n_hough->get_param_2();
    ImGui::SetNextItemWidth(125);
    ImGui::SliderFloat("Parameter 2", param_2, 1.0f, 100.0f, "%.1f");

    ImGui::Unindent();
  }

  //Ratio
  int* ratio = k4n_hough->get_ratio();
  ImGui::SetNextItemWidth(150);
  ImGui::SliderInt("Ratio", ratio, 1, 100);

  //Min distance
  int* min_dist = k4n_hough->get_min_dist();
  ImGui::SetNextItemWidth(150);
  ImGui::SliderInt("Min distance", min_dist, 0, 100);

  //Min radius
  int* min_radius = k4n_hough->get_min_radius();
  ImGui::SetNextItemWidth(150);
  ImGui::SliderInt("Min radius", min_radius, 0, 100);

  //Max radius
  int* max_radius = k4n_hough->get_max_radius();
  ImGui::SetNextItemWidth(150);
  ImGui::SliderInt("Max radius", max_radius, 0, 100);

  //---------------------------
  ImGui::Separator();
}


}
