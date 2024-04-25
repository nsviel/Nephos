#include "Detection.h"

#include <K4N/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Radiometry/Namespace.h>


namespace radio::gui{

//Constructor / Destructor
Detection::Detection(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  radio::Node* node_radio = node_k4n->get_node_radio();

  this->radio_hough = node_radio->get_radio_hough();
  this->k4n_struct = node_k4n->get_k4n_struct();
  this->stream = new eng::gui::Stream(node_engine);

  //---------------------------
}
Detection::~Detection(){}

//Main function
void Detection::draw_detection(k4n::dev::Sensor* sensor){
  //---------------------------

  this->detection_parameter(sensor);

  ImGui::BeginTable("Detection##table", 2);
  this->canny_parameter(sensor);
  this->hough_parameter(sensor);
  this->ransac_parameter(sensor);
  ImGui::EndTable();
  ImGui::Separator();

  this->draw_result(sensor);

  //---------------------------
}

//Subfunction
void Detection::detection_parameter(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Parameter");

  //Pixel diviser
  ImGui::SetNextItemWidth(150);
  ImGui::SliderInt("Pixel diviser", &sensor->master->operation.intensity_diviser, 1, 5000);

  //---------------------------
}
void Detection::canny_parameter(k4n::dev::Sensor* sensor){
  //---------------------------

  //Canny
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Canny");

  ImGui::TableNextColumn();
  if(ImGui::TreeNode("Parameter##Canny")){
    //Activated
    ImGui::Checkbox("##Canny", &k4n_struct->radio.detection.canny.apply);

    //Lower threshold
    ImGui::SetNextItemWidth(125);
    ImGui::SliderInt("Lower threshold", &k4n_struct->radio.detection.canny.lower_threshold, 0, 200);

    //Upper threshold
    ImGui::SetNextItemWidth(125);
    ImGui::SliderInt("Upper threshold", &k4n_struct->radio.detection.canny.upper_threshold, 0, 200);

    ImGui::TreePop();
  }

  //---------------------------
}
void Detection::hough_parameter(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Hough");

  ImGui::TableNextColumn();
  if(ImGui::TreeNode("Parameter##Hough")){
    //Mode
    int& mode = k4n_struct->radio.detection.hough.mode;
    if(ImGui::RadioButton("Gradient", &mode, radio::hough::GRADIENT)){
      radio_hough->find_mode_parameter(mode);
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("Gradient Alt", &mode, radio::hough::GRADIENT_ALT)){
      radio_hough->find_mode_parameter(mode);
    }

    //Lower threshold
    ImGui::SetNextItemWidth(125);
    ImGui::SliderFloat("Detector threshold", &k4n_struct->radio.detection.hough.param_1, 0.1f, 500.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

    //Upper threshold
    ImGui::SetNextItemWidth(125);
    ImGui::SliderFloat("Accumulator threshold", &k4n_struct->radio.detection.hough.param_2, 0.1f, 500.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

    //Ratio
    ImGui::SetNextItemWidth(150);
    ImGui::SliderInt("Ratio", &k4n_struct->radio.detection.hough.ratio, 1, 100);
    ImGui::SetItemTooltip("This parameter affects the spacing of the accumulator cells, which in turn affects the sensitivity of the circle detection algorithm.");

    //Min distance
    ImGui::SetNextItemWidth(150);
    ImGui::SliderInt("Min distance", &k4n_struct->radio.detection.hough.min_dist, 1, 100);

    //Radius range
    int* min_radius = &k4n_struct->radio.detection.hough.min_radius;
    int* max_radius = &k4n_struct->radio.detection.hough.max_radius;
    ImGui::DragIntRange2("Radius", min_radius, max_radius, 1, 0, 100, "Min: %d px", "Max: %d px");

    //Circle drawing mode
    ImGui::Text("Draw");
    ImGui::SameLine();
    ImGui::RadioButton("All sphere", &k4n_struct->radio.detection.hough.drawing_mode, radio::hough::ALL);
    ImGui::SameLine();
    ImGui::RadioButton("Best sphere", &k4n_struct->radio.detection.hough.drawing_mode, radio::hough::BEST);

    ImGui::TreePop();
  }

  //---------------------------
}
void Detection::ransac_parameter(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Ransac");

  ImGui::TableNextColumn();
  if(ImGui::TreeNode("Parameter##Ransac")){
    ImGui::SliderInt("Num iteration", &k4n_struct->radio.detection.ransac.nb_iter, 1, 10000);
    ImGui::SliderFloat("Threshold sphere", &k4n_struct->radio.detection.ransac.thres_sphere, 0.01f, 0.1f, "%.2f m");
    ImGui::SliderFloat("Threshold pose", &k4n_struct->radio.detection.ransac.thres_pose, 0.01f, 1.0f, "%.2f m");
    ImGui::SliderFloat("Threshold radius", &k4n_struct->radio.detection.ransac.thres_radius, 0.01f, 0.1f, "%.2f m");
    ImGui::SliderFloat("Diamter x area", &k4n_struct->radio.detection.ransac.search_diameter_x, 0.5f, 5.0f, "%.1f m");

    ImGui::TreePop();
  }

  //---------------------------
}
void Detection::draw_result(k4n::dev::Sensor* sensor){
  //---------------------------

  //Display number of detected spheres
  string nb_detection = to_string(sensor->detection.nb_detection);
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Detection");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", nb_detection.c_str());

  //Display image with detected spheres
  if(sensor->image.hough.size == 0) return;
  ImVec2 image_size = ImGui::GetContentRegionAvail();
  image_size.y -= 5;
  stream->draw_stream(&sensor->image.hough, image_size);

  //---------------------------
  ImGui::Separator();
}

}
