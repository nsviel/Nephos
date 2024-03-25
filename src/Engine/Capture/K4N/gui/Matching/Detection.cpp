#include "Detection.h"

#include <K4N/Namespace.h>
#include <Render/Namespace.h>
#include <Engine/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Detection::Detection(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  k4n::matching::Node* node_matching = node_k4n->get_node_matching();

  this->k4n_hough = node_matching->get_k4n_hough();
  this->k4n_struct = node_k4n->get_k4n_struct();
  this->stream = new eng::render::gui::Stream(node_engine);
  this->gui_player = node_k4n->get_k4n_gui_player();

  //---------------------------
}
Detection::~Detection(){}

//Main function
void Detection::draw_detection(k4n::dev::Sensor* sensor){
  //---------------------------

  this->canny_parameter(sensor);
  this->hough_parameter(sensor);
  this->draw_result(sensor);

  //---------------------------
}

//Subfunction
void Detection::model_parameter(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Model parameter");

  //Detection sphere radius
  ImGui::SetNextItemWidth(150);
  ImGui::SliderFloat("Sphere diameter", &sensor->detection.sphere_diameter, 0.001, 0.5f, "%.3f m");

  //Detection sphere radius
  ImGui::SetNextItemWidth(150);
  ImGui::SliderFloat("Bounding box factor", &k4n_struct->matching.bbox.scale, 1.0f, 10.0f, "%.2fx");

  //Pixel diviser
  ImGui::SetNextItemWidth(150);
  ImGui::SliderInt("Pixel diviser", &sensor->master->operation.intensity_diviser, 1, 5000);

  //---------------------------
  ImGui::Separator();
}
void Detection::canny_parameter(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Hough parameter");

  //Canny
  ImGui::Checkbox("Canny", &k4n_struct->matching.canny.apply);

  ImGui::SameLine();
  if(ImGui::TreeNode("Parameter##Canny")){
    ImGui::Indent();

    //Lower threshold
    ImGui::SetNextItemWidth(125);
    ImGui::SliderInt("Lower threshold", &k4n_struct->matching.canny.lower_threshold, 0, 200);

    //Upper threshold
    ImGui::SetNextItemWidth(125);
    ImGui::SliderInt("Upper threshold", &k4n_struct->matching.canny.upper_threshold, 0, 200);

    ImGui::Unindent();
    ImGui::TreePop();
  }

  //---------------------------
}
void Detection::hough_parameter(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::Checkbox("Hough", &k4n_struct->matching.hough.apply);

  ImGui::SameLine();
  if(ImGui::TreeNode("Parameter##Hough")){
    ImGui::Indent();

    //Mode
    int& mode = k4n_struct->matching.hough.mode;
    if(ImGui::RadioButton("Gradient", &mode, k4n::hough::GRADIENT)){
      k4n_hough->find_mode_parameter(mode);
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("Gradient Alt", &mode, k4n::hough::GRADIENT_ALT)){
      k4n_hough->find_mode_parameter(mode);
    }

    //Lower threshold
    ImGui::SetNextItemWidth(125);
    ImGui::SliderFloat("Detector threshold", &k4n_struct->matching.hough.param_1, 0.1f, 500.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

    //Upper threshold
    ImGui::SetNextItemWidth(125);
    ImGui::SliderFloat("Accumulator threshold", &k4n_struct->matching.hough.param_2, 0.1f, 500.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

    //Ratio
    ImGui::SetNextItemWidth(150);
    ImGui::SliderInt("Ratio", &k4n_struct->matching.hough.ratio, 1, 100);
    ImGui::SetItemTooltip("This parameter affects the spacing of the accumulator cells, which in turn affects the sensitivity of the circle detection algorithm.");

    //Min distance
    ImGui::SetNextItemWidth(150);
    ImGui::SliderInt("Min distance", &k4n_struct->matching.hough.min_dist, 1, 100);

    //Radius range
    int* min_radius = &k4n_struct->matching.hough.min_radius;
    int* max_radius = &k4n_struct->matching.hough.max_radius;
    ImGui::DragIntRange2("Radius", min_radius, max_radius, 1, 0, 100, "Min: %d px", "Max: %d px");

    ImGui::Unindent();
  }

  //---------------------------
  ImGui::Separator();
}
void Detection::draw_result(k4n::dev::Sensor* sensor){
  //---------------------------

  //Display number of detected spheres
  string nb_detection = to_string(sensor->detection.nb_detection);
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Detection");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", nb_detection.c_str());

  //Circle drawing mode
  ImGui::SameLine();
  ImGui::RadioButton("All sphere", &k4n_struct->matching.hough.drawing_mode, k4n::hough::ALL);
  ImGui::SameLine();
  ImGui::RadioButton("Best sphere", &k4n_struct->matching.hough.drawing_mode, k4n::hough::BEST);

  //Player & validation
  gui_player->player_start(sensor->master);
  ImGui::SameLine();
  if(ImGui::Button("Validate")){
    if(sensor->detection.nb_detection > 0){

    }
  }
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "(%s)", k4n_struct->matching.calibration.state.c_str());

  //Display image with detected spheres
  if(sensor->image.hough.size == 0) return;
  ImVec2 image_size = ImGui::GetContentRegionAvail();
  image_size.y -= 5;
  stream->draw_stream(&sensor->image.hough, image_size);

  //---------------------------
  ImGui::Separator();
}

}
