#include "Detection.h"

#include <Engine/Namespace.h>
#include <Radiometry/Namespace.h>
#include <GUI/Namespace.h>


namespace rad::gui{

//Constructor / Destructor
Detection::Detection(rad::Node* node_radio){
  //---------------------------

  eng::Node* node_engine = node_radio->get_node_engine();

  this->rad_detection = new rad::Detection(node_radio);
  this->rad_struct = node_radio->get_rad_struct();
  this->rad_hough = new rad::detection::Hough(node_radio);
  this->stream = new gui_media::Stream(node_engine);

  //---------------------------
}
Detection::~Detection(){}

//Main function
void Detection::draw_detection_tab(){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Parameter");

  this->detection_step();
  this->detection_parameter();

  ImGui::BeginTable("Detection##table", 2);
  this->parameter_canny();
  this->parameter_hough();
  this->parameter_ransac();
  ImGui::EndTable();
  ImGui::Separator();

  this->display_image();

  //---------------------------
}

//Subfunction
void Detection::detection_step(){
  //---------------------------

  //Detection validation
  int step = rad_detection->get_step();
  if(step == rad::detection::WAIT_VALIDATION){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
    if(ImGui::Button("Validate##calibration", ImVec2(120, 0))){
      //rad_detection->next_step();
    }
    ImGui::PopStyleColor(2);
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 45, 45, 255));
    if(ImGui::Button("Stop##calibration", ImVec2(120, 0))){
      //rad_detection->next_step();
    }
    ImGui::PopStyleColor(2);
  }
  ImGui::SameLine();

  //Calibration step
  string step_str = rad_detection->get_step_str();
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "(%s)", step_str.c_str());

  //---------------------------
}
void Detection::detection_parameter(){
  //---------------------------

  ImGui::SetNextItemWidth(120);
  ImGui::SliderFloat("Sphere diameter", &rad_struct->detection.sphere_diameter, 0.001, 0.5f, "%.3f m");

  //Pixel diviser
  //ImGui::SetNextItemWidth(120);
  //ImGui::SliderInt("Pixel diviser", &sensor->master->operation.intensity_diviser, 1, 5000);

  //---------------------------
}
void Detection::parameter_canny(){
  //---------------------------

  //Canny
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Canny");

  ImGui::TableNextColumn();
  if(ImGui::TreeNode("Parameter##Canny")){
    //Activated
    ImGui::Checkbox("##Canny", &rad_struct->detection.canny.apply);

    //Lower threshold
    ImGui::SetNextItemWidth(120);
    ImGui::SliderInt("Lower threshold", &rad_struct->detection.canny.lower_threshold, 0, 200);

    //Upper threshold
    ImGui::SetNextItemWidth(120);
    ImGui::SliderInt("Upper threshold", &rad_struct->detection.canny.upper_threshold, 0, 200);

    ImGui::TreePop();
  }

  //---------------------------
}
void Detection::parameter_hough(){
  //---------------------------

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Hough");

  ImGui::TableNextColumn();
  if(ImGui::TreeNode("Parameter##Hough")){
    //Mode
    int& mode = rad_struct->detection.hough.mode;
    if(ImGui::RadioButton("Gradient", &mode, rad::hough::GRADIENT)){
      rad_hough->find_mode_parameter(mode);
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("Gradient Alt", &mode, rad::hough::GRADIENT_ALT)){
      rad_hough->find_mode_parameter(mode);
    }

    //Lower threshold
    ImGui::SetNextItemWidth(120);
    ImGui::SliderFloat("Detector threshold", &rad_struct->detection.hough.param_1, 0.1f, 500.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

    //Upper threshold
    ImGui::SetNextItemWidth(120);
    ImGui::SliderFloat("Accumulator threshold", &rad_struct->detection.hough.param_2, 0.1f, 500.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

    //Ratio
    ImGui::SetNextItemWidth(120);
    ImGui::SliderInt("Ratio", &rad_struct->detection.hough.ratio, 1, 100);
    ImGui::SetItemTooltip("This parameter affects the spacing of the accumulator cells, which in turn affects the sensitivity of the circle detection algorithm.");

    //Min distance
    ImGui::SetNextItemWidth(120);
    ImGui::SliderInt("Min distance", &rad_struct->detection.hough.min_dist, 1, 100);

    //Radius range
    int* min_radius = &rad_struct->detection.hough.min_radius;
    int* max_radius = &rad_struct->detection.hough.max_radius;
    ImGui::DragIntRange2("Radius", min_radius, max_radius, 1, 0, 100, "Min: %d px", "Max: %d px");

    //Circle drawing mode
    ImGui::Text("Draw");
    ImGui::SameLine();
    ImGui::RadioButton("All sphere", &rad_struct->detection.hough.drawing_mode, rad::hough::ALL);
    ImGui::SameLine();
    ImGui::RadioButton("Best sphere", &rad_struct->detection.hough.drawing_mode, rad::hough::BEST);

    ImGui::TreePop();
  }

  //---------------------------
}
void Detection::parameter_ransac(){
  //---------------------------

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Ransac");

  ImGui::TableNextColumn();
  if(ImGui::TreeNode("Parameter##Ransac")){
    ImGui::SetNextItemWidth(120);
    ImGui::SliderInt("Num iteration", &rad_struct->detection.ransac.nb_iter, 1, 10000);
    ImGui::SetNextItemWidth(120);
    ImGui::SliderFloat("Threshold sphere", &rad_struct->detection.ransac.thres_sphere, 0.01f, 0.1f, "%.2f m");
    ImGui::SetNextItemWidth(120);
    ImGui::SliderFloat("Threshold pose", &rad_struct->detection.ransac.thres_pose, 0.01f, 1.0f, "%.2f m");
    ImGui::SetNextItemWidth(120);
    ImGui::SliderFloat("Threshold radius", &rad_struct->detection.ransac.thres_radius, 0.01f, 0.1f, "%.2f m");
    ImGui::SetNextItemWidth(120);
    ImGui::SliderFloat("Diamter x area", &rad_struct->detection.ransac.search_diameter_x, 0.5f, 5.0f, "%.1f m");

    ImGui::TreePop();
  }

  //---------------------------
}
void Detection::display_image(){
  //---------------------------

  //Display number of detected spheres
  string nb_detection = to_string(rad_struct->detection.nb_detection);
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Detection");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", nb_detection.c_str());

  //Display image with detected spheres
  if(rad_struct->detection.hough.image.size == 0) return;
  ImVec2 image_size = ImGui::GetContentRegionAvail();
  image_size.y -= 5;
  stream->draw_stream(&rad_struct->detection.hough.image, image_size);

  //---------------------------
  ImGui::Separator();
}

}
