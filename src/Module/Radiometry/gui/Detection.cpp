#include "Detection.h"

#include <Kinect/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Radiometry/Namespace.h>
#include <GUI/Namespace.h>


namespace rad::gui{

//Constructor / Destructor
Detection::Detection(rad::Node* node_radio){
  //---------------------------

  eng::Node* node_engine = node_radio->get_node_engine();

  this->radio_struct = node_radio->get_radio_struct();
  this->radio_hough = new rad::detection::Hough(node_radio);
  this->stream = new gui_element::Stream(node_engine);

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
    ImGui::Checkbox("##Canny", &radio_struct->detection.canny.apply);

    //Lower threshold
    ImGui::SetNextItemWidth(125);
    ImGui::SliderInt("Lower threshold", &radio_struct->detection.canny.lower_threshold, 0, 200);

    //Upper threshold
    ImGui::SetNextItemWidth(125);
    ImGui::SliderInt("Upper threshold", &radio_struct->detection.canny.upper_threshold, 0, 200);

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
    int& mode = radio_struct->detection.hough.mode;
    if(ImGui::RadioButton("Gradient", &mode, rad::hough::GRADIENT)){
      radio_hough->find_mode_parameter(mode);
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("Gradient Alt", &mode, rad::hough::GRADIENT_ALT)){
      radio_hough->find_mode_parameter(mode);
    }

    //Lower threshold
    ImGui::SetNextItemWidth(125);
    ImGui::SliderFloat("Detector threshold", &radio_struct->detection.hough.param_1, 0.1f, 500.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

    //Upper threshold
    ImGui::SetNextItemWidth(125);
    ImGui::SliderFloat("Accumulator threshold", &radio_struct->detection.hough.param_2, 0.1f, 500.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

    //Ratio
    ImGui::SetNextItemWidth(150);
    ImGui::SliderInt("Ratio", &radio_struct->detection.hough.ratio, 1, 100);
    ImGui::SetItemTooltip("This parameter affects the spacing of the accumulator cells, which in turn affects the sensitivity of the circle detection algorithm.");

    //Min distance
    ImGui::SetNextItemWidth(150);
    ImGui::SliderInt("Min distance", &radio_struct->detection.hough.min_dist, 1, 100);

    //Radius range
    int* min_radius = &radio_struct->detection.hough.min_radius;
    int* max_radius = &radio_struct->detection.hough.max_radius;
    ImGui::DragIntRange2("Radius", min_radius, max_radius, 1, 0, 100, "Min: %d px", "Max: %d px");

    //Circle drawing mode
    ImGui::Text("Draw");
    ImGui::SameLine();
    ImGui::RadioButton("All sphere", &radio_struct->detection.hough.drawing_mode, rad::hough::ALL);
    ImGui::SameLine();
    ImGui::RadioButton("Best sphere", &radio_struct->detection.hough.drawing_mode, rad::hough::BEST);

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
    ImGui::SliderInt("Num iteration", &radio_struct->detection.ransac.nb_iter, 1, 10000);
    ImGui::SliderFloat("Threshold sphere", &radio_struct->detection.ransac.thres_sphere, 0.01f, 0.1f, "%.2f m");
    ImGui::SliderFloat("Threshold pose", &radio_struct->detection.ransac.thres_pose, 0.01f, 1.0f, "%.2f m");
    ImGui::SliderFloat("Threshold radius", &radio_struct->detection.ransac.thres_radius, 0.01f, 0.1f, "%.2f m");
    ImGui::SliderFloat("Diamter x area", &radio_struct->detection.ransac.search_diameter_x, 0.5f, 5.0f, "%.1f m");

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
