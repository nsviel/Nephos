#include "Model.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::gui{

//Constructor / Destructor
Model::Model(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_measure = node_radio->get_model_measure();
  this->rad_model = node_radio->get_rad_model();
  this->rad_plot = node_radio->get_model_plot();
  this->utl_plot = new utl::implot::Plot();

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::draw_tab(){
  //---------------------------

  //Parameter
  ImGui::BeginTable("Model##table", 3);
  this->parameter_measure();
  this->parameter_model();
  ImGui::EndTable();
  ImGui::Separator();

  //Plots
  float height = ImGui::GetContentRegionAvail().y / 3-3.33;
  this->plot_measure_IfR(height);
  this->plot_measure_IfIt(height);
  this->plot_model_heatmap(height);

  //---------------------------
}

//Subfunction
void Model::parameter_measure(){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  rad::structure::Plot* plot = &rad_struct->model.plot;
  //---------------------------

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Measure");
  ImGui::TableNextColumn();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button(ICON_FA_DOWNLOAD "##measure_load", ImVec2(25, 0))){
    rad_measure->import_measure();
  }
  ImGui::SameLine();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 100, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 80, 255));
  if(ImGui::Button(ICON_FA_PLAY "##measure_plot", ImVec2(25, 0))){
    rad_plot->plot_measure();
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
    ImGui::DragFloatRange2("Heatmap scale",&plot->IfRIt.axis_z.min, &plot->IfRIt.axis_z.max, 100, 0, 60000, "%.0f");

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
void Model::parameter_model(){
  rad::structure::Optimization* optim = &rad_struct->model.optim;
  rad::structure::Plot* plot = &rad_struct->model.plot;
  //---------------------------

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Model");
  ImGui::TableNextColumn();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button(ICON_FA_DOWNLOAD "##model_load", ImVec2(25, 0))){
    rad_model->import_model();
  }
  ImGui::SameLine();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 100, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 80, 255));
  if(ImGui::Button(ICON_FA_PLAY "##model_plot", ImVec2(25, 0))){
    rad_plot->plot_model();
  }
  ImGui::PopStyleColor(2);

  ImGui::TableNextColumn();
  if(ImGui::TreeNode("Parameter##Model")){
    //Path
    if(ImGui::Button("...##path_model")){
      zenity::selection_file(optim->path);
    }
    ImGui::SameLine();
    if(ImGui::Button(ICON_FA_FOLDER "##path_model")){
      utl::directory::open(optim->path);
    }
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%s", optim->path.c_str());

    //Model parameter
    ImGui::SetNextItemWidth(100);
    ImGui::DragInt("##degree_x", &optim->degree_x, 1, 1, 10);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    ImGui::DragInt("Degree", &optim->degree_y, 1, 1, 10);
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "RMSE: %.4f", optim->rmse);
    if(ImGui::DragFloatRange2("Range x",&optim->axis_x.bound[0], &optim->axis_x.bound[1], 0.1, 0, 10, "%.2fm", "%.2fm")){
      rad_plot->update_plot_data();
    }
    if(ImGui::DragFloatRange2("Range y",&optim->axis_y.bound[0], &optim->axis_y.bound[1], 1, 0, 90, "%.0f°", "%.0f°")){
      rad_plot->update_plot_data();
    }

    //Model function
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 100, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 80, 255));
    if(ImGui::Button("Compute##model", ImVec2(120, 0))){
      rad_model->compute_model();
    }
    ImGui::SameLine();
    if(ImGui::Button("Plot##model", ImVec2(120, 0))){
      rad_plot->plot_model();
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

//Plot function
void Model::plot_measure_IfR(float height){
  rad::structure::Plot* plot = &rad_struct->model.plot;
  //---------------------------

  plot->IfR.dimension = ivec2(-1, height);
  utl_plot->plot_regression(&plot->IfR);

  //---------------------------
}
void Model::plot_measure_IfIt(float height){
  rad::structure::Plot* plot = &rad_struct->model.plot;
  //---------------------------

  plot->IfIt.dimension = ivec2(-1, height);
  utl_plot->plot_regression(&plot->IfIt);

  //---------------------------
}
void Model::plot_model_heatmap(float height){
  rad::structure::Measure* measure = &rad_struct->model.measure;
  rad::structure::Optimization* optim = &rad_struct->model.optim;
  rad::structure::Plot* plot = &rad_struct->model.plot;
  //---------------------------

  plot->IfRIt.dimension = ivec2(-1, height);
  bool need_update = utl_plot->plot_heatmap(&plot->IfRIt, &optim->axis_x, &optim->axis_y);
  if(need_update){
    rad_plot->update_plot_data();
  }

  //---------------------------
}

}
