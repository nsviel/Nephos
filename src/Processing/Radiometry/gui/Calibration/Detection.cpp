#include "Detection.h"

#include <Utility/Namespace.h>
#include <Core/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Data/Namespace.h>


namespace rad::gui::calibration{

//Constructor / Destructor
Detection::Detection(rad::Node* node_radio){
  //---------------------------

  dat::Node* node_data = node_radio->get_node_data();
  eng::Node* node_engine = node_radio->get_node_engine();
  rad::calibration::Node* node_calibration = node_radio->get_node_calibration();

  this->rad_struct = node_calibration->get_rad_struct();
  this->rad_process = node_calibration->get_rad_process();
  this->stream = new rnd::gui::Stream(node_engine);
  this->dat_image = node_data->get_dat_image();

  //---------------------------
}
Detection::~Detection(){}

//Main function
void Detection::draw_tab(dyn::base::Sensor* sensor){
  //---------------------------

  this->detection_step();
  this->detection_parameter();
  this->detection_image(sensor);

  //---------------------------
}

//Subfunction
void Detection::detection_step(){
  //---------------------------

  ImGui::BeginTable("detection_step##table", 3);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 100.0f);
  ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthFixed, 15.0f);
  ImGui::TableSetupColumn("three", ImGuiTableColumnFlags_WidthStretch);

  //Detection step
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Detection");
  ImGui::TableNextColumn();
  if(rad_struct->state.detection == rad::calibration::detection::PROCESSING){
    ImGui::Spinner_cicle(ImVec4(1, 1, 1, 1));
  }
  ImGui::TableNextColumn();
  if(rad_struct->state.detection == rad::calibration::detection::WAIT_VALIDATION){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
    if(ImGui::Button("Validate##sphere_detection", ImVec2(120, 0))){
      rad_process->step_detection();
    }
    ImGui::PopStyleColor(2);
  }else if(rad_struct->state.detection == rad::calibration::detection::PROCESSING){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 45, 45, 255));
    if(ImGui::Button("Stop##sphere_detection", ImVec2(120, 0))){
      rad_process->step_detection();
    }
    ImGui::PopStyleColor(2);
  }

  //Measure step
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Measure");
  ImGui::TableNextColumn();
  if(rad_struct->state.measure == rad::calibration::measure::PROCESSING){
    ImGui::Spinner_cicle(ImVec4(1, 1, 1, 1));
  }else{
    switch(rad_struct->state.data){
      case rad::calibration::NO_DATA:{
        ImGui::Cross(ImVec4(1, 0.4, 0.4, 1));
        break;
      }
      case rad::calibration::HAS_DATA:{
        ImGui::Check_on();
        break;
      }
    }
  }
  ImGui::TableNextColumn();
  if(rad_struct->state.measure == rad::calibration::measure::WAIT_VALIDATION){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
    if(ImGui::Button("Validate##sphere_measure", ImVec2(120, 0))){
      rad_process->step_measure();
    }
    ImGui::PopStyleColor(2);
  }else if(rad_struct->state.measure == rad::calibration::measure::PROCESSING){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 45, 45, 255));
    if(ImGui::Button("Stop##sphere_measure", ImVec2(120, 0))){
      rad_process->step_measure();
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

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Detection::detection_image(dyn::base::Sensor* sensor){
  ImVec2 available_space = ImGui::GetContentRegionAvail();
  //---------------------------

  //Display image with detected spheres
  utl::media::Image* image = dat_image->get_image(sensor, "Detection");
  if(image == nullptr) return;
  stream->draw_stream(image, ImVec2(available_space.x, available_space.y - 5));

  //---------------------------
  ImGui::Separator();
}
void Detection::parameter_canny(){
  //---------------------------

  //Canny
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Canny");

  ImGui::TableNextColumn();
  if(ImGui::TreeNode("Parameter##Canny")){
    //Activated
    ImGui::Checkbox("##Canny", &rad_struct->canny.apply);

    //Lower threshold
    ImGui::SetNextItemWidth(120);
    ImGui::SliderInt("Lower threshold", &rad_struct->canny.thres_lower, 0, 1000);

    //Upper threshold
    ImGui::SetNextItemWidth(120);
    ImGui::SliderInt("Upper threshold", &rad_struct->canny.thres_upper, 0, 1000);

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
    //ImGui::SliderInt("Pixel diviser", &sensor->set_parent->operation.intensity_diviser, 1, 5000);

    //Mode
    int& mode = rad_struct->hough.mode;
    if(ImGui::RadioButton("Gradient", &mode, rad::hough::GRADIENT)){
      rad_struct->hough.param_1 = 100; //higher threshold for the Canny edge detector
      rad_struct->hough.param_2 = 40; //accumulator threshold for the circle centers at the detection stage
      rad_struct->hough.cv_mode = cv::HOUGH_GRADIENT;
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("Gradient Alt", &mode, rad::hough::GRADIENT_ALT)){
      rad_struct->hough.param_1 = 300;
      rad_struct->hough.param_2 = 0.9;
      rad_struct->hough.cv_mode = cv::HOUGH_GRADIENT_ALT;
    }

    //Lower threshold
    ImGui::SetNextItemWidth(120);
    ImGui::SliderFloat("Detector threshold", &rad_struct->hough.param_1, 0.1f, 500.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

    //Upper threshold
    ImGui::SetNextItemWidth(120);
    ImGui::SliderFloat("Accumulator threshold", &rad_struct->hough.param_2, 0.1f, 500.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

    //Ratio
    ImGui::SetNextItemWidth(120);
    ImGui::SliderInt("Ratio", &rad_struct->hough.ratio, 1, 100);
    ImGui::SetItemTooltip("This parameter affects the spacing of the accumulator cells, which in turn affects the sensitivity of the circle detection algorithm.");

    //Min distance
    ImGui::SetNextItemWidth(120);
    ImGui::SliderInt("Min distance", &rad_struct->hough.min_dist, 1, 100);

    //Radius range
    int* min_radius = &rad_struct->hough.min_radius;
    int* max_radius = &rad_struct->hough.max_radius;
    ImGui::DragIntRange2("Radius", min_radius, max_radius, 1, 0, 500, "Min: %d px", "Max: %d px");

    //Circle drawing mode
    ImGui::Text("Draw");
    ImGui::SameLine();
    ImGui::RadioButton("All sphere", &rad_struct->hough.draw, rad::hough::ALL);
    ImGui::SameLine();
    ImGui::RadioButton("Best sphere", &rad_struct->hough.draw, rad::hough::BEST);

    ImGui::TreePop();
  }

  //---------------------------
}

}
