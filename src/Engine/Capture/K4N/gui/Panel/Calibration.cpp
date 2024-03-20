#include "Calibration.h"

#include <K4N/Namespace.h>
#include <Render/Namespace.h>
#include <Engine/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Calibration::Calibration(k4n::Node* node_k4n, bool* show_window){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();

  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->k4n_model = node_k4n->get_k4n_model();
  this->k4n_hough = k4n_model->get_k4n_hough();
  this->stream = new eng::render::gui::Stream(node_engine);

  this->show_window = show_window;
  this->name = "Calibration";

  //---------------------------
}
Calibration::~Calibration(){}

//Main function
void Calibration::run_panel(){
  k4n::dev::Master* master = k4n_swarm->get_selected_master();
  //---------------------------

  if(*show_window){
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
  k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(master->selected_entity);
  //---------------------------

  this->model_parameter(sensor);
  this->hough_parameter(sensor);
  this->draw_result(sensor);

  //---------------------------
}

//Subfunction
void Calibration::model_parameter(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Model parameter");

  //Calibration sphere radius
  ImGui::SetNextItemWidth(150);
  ImGui::SliderFloat("Sphere diameter", &sensor->calibration.sphere_diameter, 0.001, 0.5f, "%.3f m");

  //Pixel diviser
  ImGui::SetNextItemWidth(150);
  ImGui::SliderInt("Pixel diviser", &sensor->master->operation.intensity_diviser, 1, 5000);

  //---------------------------
  ImGui::Separator();
}
void Calibration::hough_parameter(k4n::dev::Sensor* sensor){
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
  int& mode = sensor->calibration.hough_mode;
  if(ImGui::RadioButton("Gradient", &mode, k4n::hough::GRADIENT)){
    k4n_hough->find_mode_parameter(mode);
  }
  ImGui::SameLine();
  if(ImGui::RadioButton("Gradient Alt", &mode, k4n::hough::GRADIENT_ALT)){
    k4n_hough->find_mode_parameter(mode);
  }

  {
    ImGui::Indent();

    //Lower threshold
    float* param_1 = k4n_hough->get_param_1();
    ImGui::SetNextItemWidth(125);
    ImGui::SliderFloat("Detector threshold", param_1, 0.1f, 500.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

    //Upper threshold
    float* param_2 = k4n_hough->get_param_2();
    ImGui::SetNextItemWidth(125);
    ImGui::SliderFloat("Accumulator threshold", param_2, 0.1f, 500.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

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

  //Radius range
  int* min_radius = k4n_hough->get_min_radius();
  int* max_radius = k4n_hough->get_max_radius();
  ImGui::DragIntRange2("Radius", min_radius, max_radius, 1, 0, 100, "Min: %d px", "Max: %d px");

  //---------------------------
  ImGui::Separator();
}
void Calibration::draw_result(k4n::dev::Sensor* sensor){
  //---------------------------

  //Circle drawing mode
  ImGui::RadioButton("All sphere", &sensor->calibration.drawing_mode, k4n::hough::ALL);
  ImGui::SameLine();
  ImGui::RadioButton("Best sphere", &sensor->calibration.drawing_mode, k4n::hough::BEST);

  //Display number of detected spheres
  string nb_detection = to_string(k4n_hough->get_nb_detection());
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Detection");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", nb_detection.c_str());

  //Display image with detected spheres
  if(sensor->image.hough.size == 0) return;
  ImVec2 image_size = ImGui::GetContentRegionAvail();
  stream->draw_stream(&sensor->image.hough, image_size);

  //---------------------------
  ImGui::Separator();
}

}
