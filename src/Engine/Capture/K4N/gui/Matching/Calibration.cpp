#include "Calibration.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Calibration::Calibration(k4n::Node* node_k4n){
  //---------------------------

  k4n::matching::Node* node_matching = node_k4n->get_node_matching();

  this->k4n_struct = node_k4n->get_k4n_struct();
  this->k4n_calibration = node_matching->get_k4n_calibration();
  this->utl_plot = new utl::implot::Plot();
  this->gui_player = node_k4n->get_k4n_gui_player();

  //---------------------------
}
Calibration::~Calibration(){}

//Main function
void Calibration::draw_calibration_player(k4n::dev::Sensor* sensor){
  //---------------------------

  //Player
  gui_player->player_start(sensor->master);
  ImGui::SameLine();

  //Detection validation
  int step = k4n_calibration->get_step();
  if(step == k4n::calibration::WAIT_VALIDATION){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
    if(ImGui::Button("Validate##calibration", ImVec2(120, 0))){
      k4n_calibration->next_step(sensor);
    }
    ImGui::PopStyleColor(2);
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 45, 45, 255));
    if(ImGui::Button("Stop##calibration", ImVec2(120, 0))){
      k4n_calibration->next_step(sensor);
    }
    ImGui::PopStyleColor(2);
  }
  ImGui::SameLine();

  //Calibration step
  string step_str = k4n_calibration->get_step_str();
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "(%s)", step_str.c_str());

  //---------------------------
}
void Calibration::draw_calibration_tab(k4n::dev::Sensor* sensor){
  //---------------------------

  this->draw_calibration_parameter(sensor);

  ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(30, 70, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_TabHovered, IM_COL32(50, 110, 120, 255));
  ImGui::PushStyleColor(ImGuiCol_TabActive, IM_COL32(40, 90, 120, 255));
  ImGui::BeginTabBar("calibration_tab##4567");

  this->tab_measure(sensor);
  this->tab_model(sensor);

  ImGui::EndTabBar();
  ImGui::PopStyleColor(3);

  //---------------------------
}
void Calibration::draw_calibration_parameter(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Parameter");

  //Canny
  ImGui::Text("RANSAC");

  ImGui::SameLine();
  if(ImGui::TreeNode("Parameter##Ransac")){
    ImGui::SliderInt("Num iteration", &k4n_struct->matching.calibration.ransac_nb_iter, 1, 10000);
    ImGui::SliderFloat("Threshold sphere", &k4n_struct->matching.calibration.ransac_thres_sphere, 0.01f, 0.1f, "%.2f m");
    ImGui::SliderFloat("Threshold pose", &k4n_struct->matching.calibration.ransac_thres_pose, 0.01f, 1.0f, "%.2f m");
    ImGui::SliderFloat("Threshold radius", &k4n_struct->matching.calibration.ransac_thres_radius, 0.01f, 0.1f, "%.2f m");
    ImGui::SliderFloat("Diamter x area", &k4n_struct->matching.calibration.ransac_search_diameter_x, 0.5f, 5.0f, "%.1f m");

    ImGui::TreePop();
  }

  //Heatmap scale
  ImGui::DragFloatRange2("Heatmap scale",&k4n_struct->matching.model.IfRIt.z_min, &k4n_struct->matching.model.IfRIt.z_max, 100, 0, 60000);

  //---------------------------
  ImGui::Separator();
}

//Measure function
void Calibration::tab_measure(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x/2-2);
  if(ImGui::BeginTabItem("Measure##calibration")){
    float height = ImGui::GetContentRegionAvail().y / 3-3.33;

    this->plot_IfR(sensor, height);
    this->plot_IfIt(sensor, height);
    this->plot_IfItR(sensor, height);

    ImGui::EndTabItem();
  }

  //---------------------------
}
void Calibration::plot_IfR(k4n::dev::Sensor* sensor, float height){
  //---------------------------

  utl::type::Plot* plot = &k4n_struct->matching.model.IfR;
  plot->dimension = ivec2(-1, height);
  utl_plot->plot_scatter(plot);

  //---------------------------
}
void Calibration::plot_IfIt(k4n::dev::Sensor* sensor, float height){
  //---------------------------

  utl::type::Plot* plot = &k4n_struct->matching.model.IfIt;
  plot->dimension = ivec2(-1, height);
  utl_plot->plot_scatter(plot);

  //---------------------------
}
void Calibration::plot_IfItR(k4n::dev::Sensor* sensor, float height){
  //---------------------------

  utl::type::Plot* plot = &k4n_struct->matching.model.IfRIt;
  plot->dimension = ivec2(-1, height);
  utl_plot->plot_heatmap(plot);

  //---------------------------
}

//Model function
void Calibration::tab_model(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x/2-2);
  if(ImGui::BeginTabItem("Model##calibration")){
    float height = ImGui::GetContentRegionAvail().y / 3-3.33;



    ImGui::EndTabItem();
  }

  //---------------------------
}

}
