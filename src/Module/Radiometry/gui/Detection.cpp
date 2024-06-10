#include "Detection.h"

#include <Utility/Namespace.h>
#include <Engine/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::gui{

//Constructor / Destructor
Detection::Detection(rad::Node* node_radio){
  //---------------------------

  eng::Node* node_engine = node_radio->get_node_engine();
  dyn::Node* node_dynamic = node_radio->get_node_dynamic();
  rad::detection::Node* node_detection = node_radio->get_node_detection();

  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->rad_struct = node_detection->get_rad_struct();
  this->node_detection = node_radio->get_node_detection();
  this->rad_circle = new rad::detection::image::Circle(node_detection);
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

  ImGui::SetNextItemWidth(100);
  ImGui::SliderInt("I diviser", &dyn_struct->operation.intensity.diviser, 1, 10000);

  ImGui::BeginTable("detection_step##table", 3);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 100.0f);
  ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthFixed, 15.0f);
  ImGui::TableSetupColumn("three", ImGuiTableColumnFlags_WidthStretch);

  //Sphere measure stuff
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Sphere measure");
  ImGui::TableNextColumn();
  this->display_state(rad_struct->sphere.state_step, rad_struct->sphere.state_data);
  ImGui::TableNextColumn();
  if(rad_struct->sphere.state_step == rad::detection::PROCESSING){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 45, 45, 255));
    if(ImGui::Button("Stop##sphere_measure", ImVec2(120, 0))){
      node_detection->step_sphere_detection();
    }
    ImGui::PopStyleColor(2);
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
    if(ImGui::Button("Validate##sphere_measure", ImVec2(120, 0))){
      node_detection->step_sphere_detection();
    }
    ImGui::PopStyleColor(2);
  }

  //Chart measure stuff
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Chart measure");
  ImGui::TableNextColumn();
  this->display_state(rad_struct->chart.state_step, rad_struct->chart.state_data);
  ImGui::TableNextColumn();
  if(rad_struct->chart.state_step == rad::detection::PROCESSING){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 45, 45, 255));
    if(ImGui::Button("Stop##chart_measure", ImVec2(120, 0))){
      node_detection->step_chart_detection();
    }
    ImGui::PopStyleColor(2);
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
    if(ImGui::Button("Validate##chart_measure", ImVec2(120, 0))){
      node_detection->step_chart_detection();
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
  string nb_detection = to_string(rad_struct->sphere.hough.nb_detection);
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Detection");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", nb_detection.c_str());

  //Display image with detected spheres
  if(rad_struct->sphere.image.size == 0) return;
  ImVec2 image_size = ImGui::GetContentRegionAvail();
  image_size.y -= 5;
  stream->draw_stream(&rad_struct->sphere.image, image_size);

  //---------------------------
  ImGui::Separator();
}
void Detection::display_state(int step, int data){
  //---------------------------

  if(step == rad::detection::PROCESSING){
    ImGui::Spinner_cicle(ImVec4(1, 1, 1, 1));
    return;
  }

  switch(data){
    case rad::detection::NO_DATA:{
      ImGui::Cross(ImVec4(1, 0.4, 0.4, 1));
      break;
    }
    case rad::detection::HAS_DATA:{
      ImGui::Check_on();
      break;
    }
  }

  //---------------------------
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
    ImGui::Checkbox("##Canny", &rad_struct->sphere.canny.apply);

    //Lower threshold
    ImGui::SetNextItemWidth(120);
    ImGui::SliderInt("Lower threshold", &rad_struct->sphere.canny.lower_threshold, 0, 200);

    //Upper threshold
    ImGui::SetNextItemWidth(120);
    ImGui::SliderInt("Upper threshold", &rad_struct->sphere.canny.upper_threshold, 0, 200);

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
    int& mode = rad_struct->sphere.hough.mode;
    if(ImGui::RadioButton("Gradient", &mode, rad::hough::GRADIENT)){
      rad_circle->find_hough_parameter(mode);
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("Gradient Alt", &mode, rad::hough::GRADIENT_ALT)){
      rad_circle->find_hough_parameter(mode);
    }

    //Lower threshold
    ImGui::SetNextItemWidth(120);
    ImGui::SliderFloat("Detector threshold", &rad_struct->sphere.hough.param_1, 0.1f, 500.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

    //Upper threshold
    ImGui::SetNextItemWidth(120);
    ImGui::SliderFloat("Accumulator threshold", &rad_struct->sphere.hough.param_2, 0.1f, 500.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

    //Ratio
    ImGui::SetNextItemWidth(120);
    ImGui::SliderInt("Ratio", &rad_struct->sphere.hough.ratio, 1, 100);
    ImGui::SetItemTooltip("This parameter affects the spacing of the accumulator cells, which in turn affects the sensitivity of the circle detection algorithm.");

    //Min distance
    ImGui::SetNextItemWidth(120);
    ImGui::SliderInt("Min distance", &rad_struct->sphere.hough.min_dist, 1, 100);

    //Radius range
    int* min_radius = &rad_struct->sphere.hough.min_radius;
    int* max_radius = &rad_struct->sphere.hough.max_radius;
    ImGui::DragIntRange2("Radius", min_radius, max_radius, 1, 0, 100, "Min: %d px", "Max: %d px");

    //Circle drawing mode
    ImGui::Text("Draw");
    ImGui::SameLine();
    ImGui::RadioButton("All sphere", &rad_struct->sphere.hough.draw, rad::hough::ALL);
    ImGui::SameLine();
    ImGui::RadioButton("Best sphere", &rad_struct->sphere.hough.draw, rad::hough::BEST);

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
    ImGui::SliderFloat("Sphere diameter", &rad_struct->sphere.ransac.sphere_diameter, 0.001, 0.5f, "%.3f m");
    ImGui::SetNextItemWidth(120);
    ImGui::SliderInt("Num iteration", &rad_struct->sphere.ransac.nb_iter, 1, 10000);
    ImGui::SetNextItemWidth(120);
    ImGui::SliderFloat("Threshold sphere", &rad_struct->sphere.ransac.thres_sphere, 0.01f, 0.1f, "%.2f m");
    ImGui::SetNextItemWidth(120);
    ImGui::SliderFloat("Threshold pose", &rad_struct->sphere.ransac.thres_pose, 0.01f, 1.0f, "%.2f m");
    ImGui::SetNextItemWidth(120);
    ImGui::SliderFloat("Threshold radius", &rad_struct->sphere.ransac.thres_radius, 0.01f, 0.1f, "%.2f m");
    ImGui::SetNextItemWidth(120);
    ImGui::SliderFloat("Diamter x area", &rad_struct->sphere.ransac.search_lambda, 0.5f, 5.0f, "%.1f m");

    ImGui::TreePop();
  }

  //---------------------------
}


}
