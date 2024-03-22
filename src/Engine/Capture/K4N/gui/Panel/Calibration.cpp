#include "Calibration.h"

#include <K4N/Namespace.h>
#include <Render/Namespace.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Calibration::Calibration(k4n::Node* node_k4n, bool* show_window){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();

  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->k4n_model = node_k4n->get_k4n_model();
  this->k4n_hough = new k4n::detection::Hough(node_k4n);
  this->k4n_struct = node_k4n->get_k4n_struct();
  this->utl_plot = new utl::implot::Plot();
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

  if(*show_window && master != nullptr){
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
  this->canny_parameter(sensor);
  this->hough_parameter(sensor);
  this->draw_result(sensor);
  this->plot_IfR(sensor);

  //---------------------------
}

//Subfunction
void Calibration::model_parameter(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Model parameter");

  //Calibration sphere radius
  ImGui::SetNextItemWidth(150);
  ImGui::SliderFloat("Sphere diameter", &sensor->detection.sphere_diameter, 0.001, 0.5f, "%.3f m");

  //Calibration sphere radius
  ImGui::SetNextItemWidth(150);
  ImGui::SliderFloat("Bounding box factor", &k4n_struct->calibration.bbox.scale, 1.0f, 10.0f, "%.2fx");

  //Pixel diviser
  ImGui::SetNextItemWidth(150);
  ImGui::SliderInt("Pixel diviser", &sensor->master->operation.intensity_diviser, 1, 5000);

  //---------------------------
  ImGui::Separator();
}
void Calibration::canny_parameter(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Hough parameter");

  //Canny
  ImGui::Checkbox("Canny", &k4n_struct->calibration.canny.apply);

  ImGui::SameLine();
  if(ImGui::TreeNode("Parameter##Canny")){
    ImGui::Indent();

    //Lower threshold
    ImGui::SetNextItemWidth(125);
    ImGui::SliderInt("Lower threshold", &k4n_struct->calibration.canny.lower_threshold, 0, 200);

    //Upper threshold
    ImGui::SetNextItemWidth(125);
    ImGui::SliderInt("Upper threshold", &k4n_struct->calibration.canny.upper_threshold, 0, 200);

    ImGui::Unindent();
    ImGui::TreePop();
  }

  //---------------------------
}
void Calibration::hough_parameter(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::Checkbox("Hough", &k4n_struct->calibration.hough.apply);

  ImGui::SameLine();
  if(ImGui::TreeNode("Parameter##Hough")){
    ImGui::Indent();

    //Mode
    int& mode = k4n_struct->calibration.hough.mode;
    if(ImGui::RadioButton("Gradient", &mode, k4n::hough::GRADIENT)){
      k4n_hough->find_mode_parameter(mode);
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("Gradient Alt", &mode, k4n::hough::GRADIENT_ALT)){
      k4n_hough->find_mode_parameter(mode);
    }

    //Lower threshold
    ImGui::SetNextItemWidth(125);
    ImGui::SliderFloat("Detector threshold", &k4n_struct->calibration.hough.param_1, 0.1f, 500.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

    //Upper threshold
    ImGui::SetNextItemWidth(125);
    ImGui::SliderFloat("Accumulator threshold", &k4n_struct->calibration.hough.param_2, 0.1f, 500.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

    //Ratio
    ImGui::SetNextItemWidth(150);
    ImGui::SliderInt("Ratio", &k4n_struct->calibration.hough.ratio, 1, 100);
    ImGui::SetItemTooltip("This parameter affects the spacing of the accumulator cells, which in turn affects the sensitivity of the circle detection algorithm.");

    //Min distance
    ImGui::SetNextItemWidth(150);
    ImGui::SliderInt("Min distance", &k4n_struct->calibration.hough.min_dist, 1, 100);

    //Radius range
    int* min_radius = &k4n_struct->calibration.hough.min_radius;
    int* max_radius = &k4n_struct->calibration.hough.max_radius;
    ImGui::DragIntRange2("Radius", min_radius, max_radius, 1, 0, 100, "Min: %d px", "Max: %d px");

    ImGui::Unindent();
  }

  //---------------------------
  ImGui::Separator();
}
void Calibration::draw_result(k4n::dev::Sensor* sensor){
  //---------------------------

  //Display number of detected spheres
  string nb_detection = to_string(sensor->detection.nb_detection);
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Detection");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", nb_detection.c_str());

  //Circle drawing mode
  ImGui::SameLine();
  ImGui::RadioButton("All sphere", &k4n_struct->calibration.hough.drawing_mode, k4n::hough::ALL);
  ImGui::SameLine();
  ImGui::RadioButton("Best sphere", &k4n_struct->calibration.hough.drawing_mode, k4n::hough::BEST);

  //Display image with detected spheres
  if(sensor->image.hough.size == 0) return;
  ImVec2 image_size = ImGui::GetContentRegionAvail();
  image_size.y -= 5;
  stream->draw_stream(&sensor->image.hough, image_size);

  //---------------------------
  ImGui::Separator();
}
void Calibration::plot_IfR(k4n::dev::Sensor* sensor){
  //---------------------------

  vector<float> x;
  vector<float> y;

  for(int i=0; i<100; i++){
    x.push_back(i);
    y.push_back(i+1);
  }

  y[50] = 5;

  utl_plot->plot_scatter_2d(x, y);

  //---------------------------
}

}
