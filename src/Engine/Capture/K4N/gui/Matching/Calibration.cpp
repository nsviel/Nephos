#include "Calibration.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>
#include <python/matplotlibcpp.h>


namespace k4n::gui{

//Constructor / Destructor
Calibration::Calibration(k4n::Node* node_k4n){
  //---------------------------

  k4n::matching::Node* node_matching = node_k4n->get_node_matching();

  this->k4n_struct = node_k4n->get_k4n_struct();
  this->k4n_calibration = node_matching->get_k4n_calibration();
  this->k4n_model = node_matching->get_k4n_model();
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

  this->draw_calibration_measure(sensor);
  this->draw_calibration_model(sensor);
  this->draw_measure(sensor);

  //---------------------------
}
void Calibration::draw_calibration_measure(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Measure");

  //Import / export / clear
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button("Import##measure", ImVec2(120, 0))){
    k4n_model->import_measure();
  }
  ImGui::PopStyleColor(2);
  ImGui::SameLine();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(100, 80, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(80, 60, 60, 255));
  if(ImGui::Button("Export##measure", ImVec2(120, 0))){
    k4n_model->export_measure();
  }
  ImGui::PopStyleColor(2);
  ImGui::SameLine();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 100, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 80, 255));
  if(ImGui::Button("Clear##measure", ImVec2(120, 0))){
    k4n_model->init();
  }
  ImGui::PopStyleColor(2);

  //Heatmap scale
  ImGui::DragFloatRange2("Heatmap scale",&k4n_struct->matching.model.IfRIt.z.min, &k4n_struct->matching.model.IfRIt.z.max, 100, 0, 60000, "%.0f");

  //---------------------------
  ImGui::Separator();
}
void Calibration::draw_calibration_model(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Model");

  ImGui::SetNextItemWidth(100);
  ImGui::SliderInt("Degree", &k4n_struct->matching.model.degree, 1, 10);
  ImGui::DragFloatRange2("Range x",&k4n_struct->matching.model.x.bound[0], &k4n_struct->matching.model.x.bound[1], 0.1, 0, 10, "%.2fm", "%.2fm");
  ImGui::DragFloatRange2("Range y",&k4n_struct->matching.model.y.bound[0], &k4n_struct->matching.model.y.bound[1], 1, 0, 90, "%.0f°", "%.0f°");

  //Model fitting & plotting
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button("Plot##model", ImVec2(120, 0))){
    this->draw_model(sensor);
  }
  ImGui::PopStyleColor(2);
  ImGui::SameLine();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(100, 80, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(80, 60, 60, 255));
  if(ImGui::Button("Export##model", ImVec2(120, 0))){
    k4n_model->export_model();
  }
  ImGui::PopStyleColor(2);

  //---------------------------
  ImGui::Separator();
}

//Subfunction
void Calibration::draw_model(k4n::dev::Sensor* sensor){
  k4n::structure::Model* model = &k4n_struct->matching.model;
  //---------------------------

  k4n_model->make_model();
  k4n_model->validation_model();

  std::vector<std::vector<double>> x, y, z;

  // Generate values for x and y
  std::vector<double> x_values;
  for(double i = model->x.bound[0]; i <= model->x.bound[1]; i += 0.1){
    x_values.push_back(i);
  }

  std::vector<double> y_values;
  for(double i = model->y.bound[0]; i <= model->y.bound[1]; i += 1.0){
    y_values.push_back(i);
  }

  // Compute z values and fill x, y, and z vectors
  for (double x_val : x_values) {
    std::vector<double> row_x, row_y, row_z;
    for (double y_val : y_values) {
      row_x.push_back(x_val);
      row_y.push_back(y_val);
      row_z.push_back(k4n_model->apply_model(x_val, y_val));
    }
    x.push_back(row_x);
    y.push_back(row_y);
    z.push_back(row_z);
  }

  matplotlibcpp::plot_surface(x, y, z);
  matplotlibcpp::show();

  //---------------------------
}
void Calibration::draw_measure(k4n::dev::Sensor* sensor){
  //---------------------------

  float height = ImGui::GetContentRegionAvail().y / 3-3.33;

  this->plot_measure_IfR(sensor, height);
  this->plot_measure_IfIt(sensor, height);
  this->plot_model_heatmap(sensor, height);

  //---------------------------
}
void Calibration::plot_measure_IfR(k4n::dev::Sensor* sensor, float height){
  //---------------------------

  utl::type::Plot* plot = &k4n_struct->matching.model.IfR;
  plot->dimension = ivec2(-1, height);
  utl_plot->plot_scatter(plot);

  //---------------------------
}
void Calibration::plot_measure_IfIt(k4n::dev::Sensor* sensor, float height){
  //---------------------------

  utl::type::Plot* plot = &k4n_struct->matching.model.IfIt;
  plot->dimension = ivec2(-1, height);
  utl_plot->plot_scatter(plot);

  //---------------------------
}
void Calibration::plot_model_heatmap(k4n::dev::Sensor* sensor, float height){
  k4n::structure::Model* model = &k4n_struct->matching.model;
  //---------------------------

  model->IfRIt.dimension = ivec2(-1, height);
  bool need_update = utl_plot->plot_heatmap(&model->IfRIt, &model->x, &model->y);
  if(need_update){
    k4n_model->update_plot();
  }

  //---------------------------
}

}
