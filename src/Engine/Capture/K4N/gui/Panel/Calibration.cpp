#include "Calibration.h"

#include <K4N/Namespace.h>
#include <Render/Namespace.h>
#include <Engine/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Calibration::Calibration(k4n::Node* node_k4n, bool* show_window){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();

  this->k4n_model = node_k4n->get_k4n_model();
  this->k4n_hough = k4n_model->get_k4n_hough();
  this->stream = new eng::render::gui::Stream(node_engine);

  this->show_window = show_window;
  this->name = "Calibration";
  this->utl_image = new utl::media::Image();

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
  this->draw_result();

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
  if(ImGui::RadioButton("Gradient", mode, k4n::hough::GRADIENT)){
    k4n_hough->find_mode_parameter();
  }
  ImGui::SameLine();
  if(ImGui::RadioButton("Gradient Alt", mode, k4n::hough::GRADIENT_ALT)){
    k4n_hough->find_mode_parameter();
  }

  {
    ImGui::Indent();

    //Lower threshold
    float* param_1 = k4n_hough->get_param_1();
    ImGui::SetNextItemWidth(125);
    ImGui::SliderFloat("Parameter 1", param_1, 0.1f, 500.0f, "%.1f");

    //Upper threshold
    float* param_2 = k4n_hough->get_param_2();
    ImGui::SetNextItemWidth(125);
    ImGui::SliderFloat("Parameter 2", param_2, 0.1f, 500.0f, "%.1f");

    ImGui::Unindent();
  }

  //Ratio
  int* ratio = k4n_hough->get_ratio();
  ImGui::SetNextItemWidth(150);
  ImGui::SliderInt("Ratio", ratio, 1, 100);
  ImGui::SetItemTooltip("This parameter affects the spacing of the accumulator cells, which in turn affects the sensitivity of the circle detection algorithm.");

  //Min distance
  int* min_dist = k4n_hough->get_min_dist();
  ImGui::SetNextItemWidth(150);
  ImGui::SliderInt("Min distance", min_dist, 1, 100);

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
void Calibration::draw_result(){
  //---------------------------

  k4n_model->detect_sphere(utl_image);

  if(utl_image->size == 0) return;
  ImVec2 image_size = ImGui::GetContentRegionAvail();
  stream->draw_stream(utl_image, image_size);

  //---------------------------
  ImGui::Separator();
}

}
