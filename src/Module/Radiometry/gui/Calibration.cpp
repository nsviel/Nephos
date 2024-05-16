#include "Calibration.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::gui{

//Constructor / Destructor
Calibration::Calibration(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_detection = new rad::Detection(node_radio);
  this->rad_measure = new rad::model::Measure(node_radio);
  this->rad_model = new rad::Model(node_radio);
  this->utl_plot = new utl::implot::Plot();
  //this->gui_player = node_k4n->get_k4n_gui_player();

  //---------------------------
}
Calibration::~Calibration(){}

//Main function
void Calibration::draw_calibration_player(){
  //---------------------------

  //Player
  //gui_player->player_start(sensor->set_parent);
  ImGui::SameLine();

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
void Calibration::draw_calibration_tab(){
  //---------------------------

  ImGui::BeginTable("Detection##table", 2);
  this->draw_calibration_measure();
  this->draw_calibration_model();
  ImGui::EndTable();
  ImGui::Separator();

  this->draw_measure();

  //---------------------------
}
void Calibration::draw_calibration_measure(){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Measure");
  ImGui::SameLine();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button(ICON_FA_DOWNLOAD "##measure_load", ImVec2(25, 0))){
    rad_measure->import_measure();
  }
  ImGui::SameLine();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 100, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 80, 255));
  if(ImGui::Button(ICON_FA_PLAY "##measure_plot", ImVec2(25, 0))){
    rad_measure->plot_measure();
  }
  ImGui::PopStyleColor(2);

  ImGui::TableNextColumn();
  if(ImGui::TreeNode("Parameter##Measure")){
    //Path
    if(ImGui::Button("...##path_measure")){
      zenity::selection_file(measure->path);
    }
    ImGui::SameLine();
    if(ImGui::Button(ICON_FA_FOLDER "##path_measure")){
      utl::directory::open(measure->path);
    }
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%s", measure->path.c_str());

    //Heatmap scale
    ImGui::DragFloatRange2("Heatmap scale",&measure->IfRIt.z.min, &measure->IfRIt.z.max, 100, 0, 60000, "%.0f");

    //Import / export / clear
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
    if(ImGui::Button("Import##measure", ImVec2(120, 0))){
      rad_measure->import_measure();
    }
    ImGui::PopStyleColor(2);
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(100, 80, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(80, 60, 60, 255));
    if(ImGui::Button("Export##measure", ImVec2(120, 0))){
      rad_measure->export_measure();
    }
    ImGui::PopStyleColor(2);
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 100, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 80, 255));
    if(ImGui::Button("Clear##measure", ImVec2(120, 0))){
      rad_measure->clear_measure();
    }
    ImGui::PopStyleColor(2);

    ImGui::TreePop();
  }

  //---------------------------
}
void Calibration::draw_calibration_model(){
  rad::structure::Optimization* model = &rad_struct->model.optim;
  //---------------------------

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Model");
  ImGui::SameLine();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button(ICON_FA_DOWNLOAD "##model_load", ImVec2(25, 0))){
    rad_model->import_model();
  }
  ImGui::SameLine();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 100, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 80, 255));
  if(ImGui::Button(ICON_FA_PLAY "##model_plot", ImVec2(25, 0))){
    rad_model->draw_model();
  }
  ImGui::PopStyleColor(2);

  ImGui::TableNextColumn();
  if(ImGui::TreeNode("Parameter##Model")){
    //Path
    if(ImGui::Button("...##path_model")){
      zenity::selection_file(model->path);
    }
    ImGui::SameLine();
    if(ImGui::Button(ICON_FA_FOLDER "##path_model")){
      utl::directory::open(model->path);
    }
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%s", model->path.c_str());

    //Model parameter
    ImGui::SetNextItemWidth(100);
    ImGui::DragInt("##degree_x", &model->degree_x, 1, 1, 10);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    ImGui::DragInt("Degree", &model->degree_y, 1, 1, 10);
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "RMSE: %.4f", model->rmse);
    if(ImGui::DragFloatRange2("Range x",&model->x.bound[0], &model->x.bound[1], 0.1, 0, 10, "%.2fm", "%.2fm")){
      rad_measure->update_plot();
    }
    if(ImGui::DragFloatRange2("Range y",&model->y.bound[0], &model->y.bound[1], 1, 0, 90, "%.0f°", "%.0f°")){
      rad_measure->update_plot();
    }

    //Model function
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 100, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 80, 255));
    if(ImGui::Button("Compute##model", ImVec2(120, 0))){
      rad_model->compute_model();
    }
    ImGui::SameLine();
    if(ImGui::Button("Plot##model", ImVec2(120, 0))){
      rad_model->draw_model();
    }
    ImGui::PopStyleColor(2);

    //Model fitting & plotting
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
    if(ImGui::Button("Import##model", ImVec2(120, 0))){
      rad_model->import_model();
    }
    ImGui::PopStyleColor(2);
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(100, 80, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(80, 60, 60, 255));
    if(ImGui::Button("Export##model", ImVec2(120, 0))){
      rad_model->export_model();
    }
    ImGui::PopStyleColor(2);

    ImGui::TreePop();
  }

  //---------------------------
}

//Subfunction
void Calibration::draw_measure(){
  //---------------------------

  float height = ImGui::GetContentRegionAvail().y / 3-3.33;

  this->plot_measure_IfR(height);
  this->plot_measure_IfIt(height);
  this->plot_model_heatmap(height);

  //---------------------------
}
void Calibration::plot_measure_IfR(float height){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  measure->IfR.dimension = ivec2(-1, height);
  utl_plot->plot_regression(&measure->IfR);

  //---------------------------
}
void Calibration::plot_measure_IfIt(float height){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  //---------------------------

  measure->IfIt.dimension = ivec2(-1, height);
  utl_plot->plot_regression(&measure->IfIt);

  //---------------------------
}
void Calibration::plot_model_heatmap(float height){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  rad::structure::Optimization* model = &rad_struct->model.optim;
  //---------------------------

  measure->IfRIt.dimension = ivec2(-1, height);
  bool need_update = utl_plot->plot_heatmap(&measure->IfRIt, &model->x, &model->y);
  if(need_update){
    rad_measure->update_plot();
  }

  //---------------------------
}

}
