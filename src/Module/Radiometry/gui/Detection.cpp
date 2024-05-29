#include "Detection.h"

#include <Engine/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::gui{

//Constructor / Destructor
Detection::Detection(rad::Node* node_radio){
  //---------------------------

  eng::Node* node_engine = node_radio->get_node_engine();

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_detection = node_radio->get_rad_detection();
  this->rad_circle = new rad::detection::image::Circle(node_radio);
  this->stream = new rnd::Stream(node_engine);

  //---------------------------
}
Detection::~Detection(){}

//Main function
void Detection::draw_tab(){
  //---------------------------

  this->detection_step();
  this->detection_parameter();
  this->display_image();

  //---------------------------
}

//Subfunction
void Detection::detection_step(){
  //---------------------------

  ImGui::BeginTable("detection_step##table", 3);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 75.0f);
  ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthFixed, 15.0f);
  ImGui::TableSetupColumn("three", ImGuiTableColumnFlags_WidthStretch);

  //Correction step
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Correction");
  ImGui::TableNextColumn();
  ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 0)); // Transparent background
  ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0, 0, 0, 0)); // Transparent background on hover
  ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0, 0, 0, 0)); // Transparent background when active
  ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0)); // Transparent border
  ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0, 0, 0, 0)); // Transparent border shadow
  ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0, 1, 0, 1)); // Green check mark
  bool truc = true;
  ImGui::Checkbox("##correction_ok", &truc);
  ImGui::PopStyleColor(6);
  ImGui::TableNextColumn();
  int correction_step = rad_detection->get_correction_step();
  if(correction_step == rad::detection::VALIDATION){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
    if(ImGui::Button("Validate##calibration", ImVec2(120, 0))){
      rad_detection->next_correction_step();
    }
    ImGui::PopStyleColor(2);
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 45, 45, 255));
    if(ImGui::Button("Stop##calibration", ImVec2(120, 0))){
      rad_detection->next_correction_step();
    }
    ImGui::PopStyleColor(2);
  }

  //Calibration step
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Calibration");
  ImGui::TableNextColumn();

  ImGui::Checkbox("##calibration_ok", &truc);
  ImGui::TableNextColumn();
  int calibration_step = rad_detection->get_calibration_step();
  if(calibration_step == rad::detection::VALIDATION){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
    if(ImGui::Button("Validate##calibration", ImVec2(120, 0))){
      rad_detection->next_calibration_step();
    }
    ImGui::PopStyleColor(2);
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 45, 45, 255));
    if(ImGui::Button("Stop##calibration", ImVec2(120, 0))){
      rad_detection->next_calibration_step();
    }
    ImGui::PopStyleColor(2);
  }

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Detection::detection_parameter(){
  //---------------------------

  ImGui::BeginTable("detection_parameter##table", 2);

  this->parameter_canny();
  this->parameter_hough();
  this->parameter_ransac();

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Detection::display_image(){
  //---------------------------

  //Display number of detected spheres
  string nb_detection = to_string(rad_struct->detection.nb_detection);
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Detection");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", nb_detection.c_str());

  //Display image with detected spheres
  if(rad_struct->detection.image.size == 0) return;
  ImVec2 image_size = ImGui::GetContentRegionAvail();
  image_size.y -= 5;
  stream->draw_stream(&rad_struct->detection.image, image_size);

  //---------------------------
  ImGui::Separator();
}

//Parameter function
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
    //Pixel diviser
    //ImGui::SetNextItemWidth(120);
    //ImGui::SliderInt("Pixel diviser", &sensor->master->operation.intensity_diviser, 1, 5000);

    //Mode
    int& mode = rad_struct->detection.hough.mode;
    if(ImGui::RadioButton("Gradient", &mode, rad::hough::GRADIENT)){
      rad_circle->find_hough_parameter(mode);
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("Gradient Alt", &mode, rad::hough::GRADIENT_ALT)){
      rad_circle->find_hough_parameter(mode);
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
    ImGui::SliderFloat("Sphere diameter", &rad_struct->detection.sphere_diameter, 0.001, 0.5f, "%.3f m");
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


}
