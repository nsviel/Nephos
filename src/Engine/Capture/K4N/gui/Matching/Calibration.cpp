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
  this->k4n_measure = node_matching->get_k4n_measure();
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
  k4n::structure::Measure* measure = &k4n_struct->matching.measure;
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Measure");

  //Path
  if(ImGui::Button("...##path_measure")){
    zenity::selection_file(measure->path);
  }
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%s", measure->path.c_str());

  //Heatmap scale
  ImGui::DragFloatRange2("Heatmap scale",&measure->IfRIt.z.min, &measure->IfRIt.z.max, 100, 0, 60000, "%.0f");

  //Import / export / clear
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button("Import##measure", ImVec2(120, 0))){
    k4n_measure->import_measure();
  }
  ImGui::PopStyleColor(2);
  ImGui::SameLine();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(100, 80, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(80, 60, 60, 255));
  if(ImGui::Button("Export##measure", ImVec2(120, 0))){
    k4n_measure->export_measure();
  }
  ImGui::PopStyleColor(2);
  ImGui::SameLine();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 100, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 80, 255));
  if(ImGui::Button("Clear##measure", ImVec2(120, 0))){
    k4n_measure->clear_measure();
  }
  ImGui::PopStyleColor(2);

  //---------------------------
  ImGui::Separator();
}
void Calibration::draw_calibration_model(k4n::dev::Sensor* sensor){
  k4n::structure::Model* model = &k4n_struct->matching.model;
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Model");

  //Path
  if(ImGui::Button("...##path_model")){
    zenity::selection_file(model->path);
  }
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%s", model->path.c_str());

  //Model parameter
  ImGui::SetNextItemWidth(100);
  ImGui::SliderInt("Degree", &model->degree, 1, 10);
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "RMSE: %.4f", model->rmse);
  ImGui::DragFloatRange2("Range x",&model->x.bound[0], &model->x.bound[1], 0.1, 0, 10, "%.2fm", "%.2fm");
  ImGui::DragFloatRange2("Range y",&model->y.bound[0], &model->y.bound[1], 1, 0, 90, "%.0f°", "%.0f°");

  //Model function
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 100, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 80, 255));
  if(ImGui::Button("Compute##model", ImVec2(120, 0))){
    k4n_model->compute_model();
  }
  ImGui::SameLine();
  if(ImGui::Button("Plot##model", ImVec2(120, 0))){
    k4n_model->draw_model();
  }
  ImGui::PopStyleColor(2);

  //Model fitting & plotting
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button("Import##model", ImVec2(120, 0))){
    k4n_model->import_model();
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
void Calibration::draw_measure(k4n::dev::Sensor* sensor){
  //---------------------------

  float height = ImGui::GetContentRegionAvail().y / 3-3.33;

  this->plot_measure_IfR(sensor, height);
  this->plot_measure_IfIt(sensor, height);
  this->plot_model_heatmap(sensor, height);

  //---------------------------
}
void Calibration::plot_measure_IfR(k4n::dev::Sensor* sensor, float height){
  k4n::structure::Measure* measure = &k4n_struct->matching.measure;
  //---------------------------

  measure->IfR.dimension = ivec2(-1, height);
  utl_plot->plot_scatter(&measure->IfR);

  //---------------------------
}
void Calibration::plot_measure_IfIt(k4n::dev::Sensor* sensor, float height){
  k4n::structure::Measure* measure = &k4n_struct->matching.measure;
  //---------------------------

  measure->IfIt.dimension = ivec2(-1, height);
  utl_plot->plot_scatter(&measure->IfIt);

  //---------------------------
}
void Calibration::plot_model_heatmap(k4n::dev::Sensor* sensor, float height){
  k4n::structure::Measure* measure = &k4n_struct->matching.measure;
  k4n::structure::Model* model = &k4n_struct->matching.model;
  //---------------------------

  measure->IfRIt.dimension = ivec2(-1, height);
  bool need_update = utl_plot->plot_heatmap(&measure->IfRIt, &model->x, &model->y);
  if(need_update){
    k4n_measure->update_plot();
  }

  //---------------------------
}

}
