#include "Model.h"

#include <Radiometry/Namespace.h>
#include <Data/Namespace.h>
#include <Processing/Namespace.h>
#include <Utility/Namespace.h>


namespace rad::cor::gui{

//Constructor / Destructor
Model::Model(rad::Node* node_radio){
  //---------------------------

  rad::cor::Node* node_correction = node_radio->get_node_correction();

  this->rad_model = node_correction->get_rad_model();
  this->rad_struct = node_correction->get_rad_struct();
  this->rad_measure = node_correction->get_rad_measure();
  this->rad_plot = node_correction->get_rad_plot();
  this->rad_io_measure = node_correction->get_rad_io_measure();
  this->rad_io_model = node_correction->get_rad_io_model();
  this->utl_plot = new utl::implot::Plot();

  //---------------------------
}
Model::~Model(){}

//Main function
void Model::draw_tab(dat::base::Sensor& sensor){
  //---------------------------

  //Parameter
  ImGui::BeginTable("Measure##model_tab", 3);
  this->parameter_measure(sensor);
  this->parameter_model(sensor);
  ImGui::EndTable();
  ImGui::Separator();

  //Measure
  float height = ImGui::GetContentRegionAvail().y / 3-3.33;
  this->plot_measure_IfR(height);
  this->plot_measure_IfIt(height);
  this->plot_model_heatmap(sensor, height);

  //---------------------------
}

//Subfunction
void Model::parameter_measure(dat::base::Sensor& sensor){
  rad::cor::structure::Plot& plot = rad_struct->plot;
  //---------------------------

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Measure");
  ImGui::TableNextColumn();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button(ICON_FA_DOWNLOAD "##measure_load", ImVec2(25, 0))){
    rad_io_measure->import_measure(sensor);
  }
  ImGui::PopStyleColor(2);

  ImGui::TableNextColumn();
  if(ImGui::TreeNode("Parameter##measure_sphere")){
    //Path
    std::string path = rad_struct->measure.path.build();
    if(ImGui::Button("...##measure_sphere")){
      zenity::selection_file(path);
    }
    ImGui::SameLine();
    if(ImGui::Button(ICON_FA_FOLDER "##measure_sphere")){
      utl::directory::open(path);
    }
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", path.c_str());

    //Heatmap scale
    ImGui::SetNextItemWidth(247.5);
    ImGui::DragFloatRange2("Heatmap scale",&plot.IfRIt.axis_z.min, &plot.IfRIt.axis_z.max, 100, 0, 60000, "%.0f");

    //Import / export / clear
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 100, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 80, 255));
    if(ImGui::Button("Plot##measure_sphere", ImVec2(120, 0))){
      rad_plot->plot_measure();
    }
    ImGui::PopStyleColor(2);
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 100, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 80, 255));
    if(ImGui::Button("Clear##measure_sphere", ImVec2(120, 0))){
      rad_io_measure->clear_measure(sensor);
    }
    ImGui::PopStyleColor(2);
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
    if(ImGui::Button("Import##measure_sphere", ImVec2(120, 0))){
      rad_io_measure->import_measure(sensor);
    }
    ImGui::PopStyleColor(2);
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(100, 80, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(80, 60, 60, 255));
    if(ImGui::Button("Export##measure_sphere", ImVec2(120, 0))){
      rad_io_measure->export_measure(sensor);
    }
    ImGui::PopStyleColor(2);

    ImGui::TreePop();
  }

  //---------------------------
}
void Model::parameter_model(dat::base::Sensor& sensor){
  dat::sensor::Model* model = rad_model->get_model(sensor, "NFOV");
  rad::cor::structure::Plot& plot = rad_struct->plot;
  //---------------------------

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Model");
  ImGui::TableNextColumn();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button(ICON_FA_DOWNLOAD "##model_load", ImVec2(25, 0))){
    rad_io_model->import_model(sensor);
  }
  ImGui::PopStyleColor(2);

  ImGui::TableNextColumn();
  if(ImGui::TreeNode("Parameter##Model")){
    //Path
    std::string path = sensor.calibration.path.build();
    if(ImGui::Button("...##path_model")){
      zenity::selection_file(path);
    }
    ImGui::SameLine();
    if(ImGui::Button(ICON_FA_FOLDER "##path_model")){
      utl::directory::open(path);
    }
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", path.c_str());

    //Model parameter
    ImGui::SetNextItemWidth(120);
    ImGui::DragInt("##degree_x", &model->degree_x, 1, 1, 10);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(120);
    ImGui::DragInt("Degree", &model->degree_y, 1, 1, 10);
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "RMSE: %.4f", model->rmse);
    ImGui::SetNextItemWidth(247.5);
    if(ImGui::DragFloatRange2("Range x",&model->axis_x.bound[0], &model->axis_x.bound[1], 0.1, 0, 10, "%.2fm", "%.2fm")){
      rad_plot->update(sensor);
    }
    ImGui::SetNextItemWidth(247.5);
    if(ImGui::DragFloatRange2("Range y",&model->axis_y.bound[0], &model->axis_y.bound[1], 1, 0, 90, "%.0f°", "%.0f°")){
      rad_plot->update(sensor);
    }

    //Model function
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 100, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 80, 255));
    if(ImGui::Button("Compute##model", ImVec2(120, 0))){
      rad_model->compute_model(sensor);
      rad_plot->update(sensor);
    }
    ImGui::PopStyleColor(2);
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 100, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 80, 255));
    if(ImGui::Button("Clear##model_sphere", ImVec2(120, 0))){
      rad_model->clear_model();
    }
    ImGui::PopStyleColor(2);

    //Model fitting & plotting
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
    if(ImGui::Button("Import##model", ImVec2(120, 0))){
      rad_io_model->import_model(sensor);
    }
    ImGui::PopStyleColor(2);
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(100, 80, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(80, 60, 60, 255));
    if(ImGui::Button("Export##model", ImVec2(120, 0))){
      rad_io_model->export_model(sensor);
    }
    ImGui::PopStyleColor(2);

    ImGui::TreePop();
  }

  //---------------------------
}

//Sphere plot function
void Model::plot_measure_IfR(float height){
  rad::cor::structure::Plot& plot = rad_struct->plot;
  //---------------------------

  if(plot.IfR.title == "") return;
  plot.IfR.dimension = glm::ivec2(-1, height);
  utl_plot->plot_regression(&plot.IfR);

  //---------------------------
}
void Model::plot_measure_IfIt(float height){
  rad::cor::structure::Plot& plot = rad_struct->plot;
  //---------------------------

  if(plot.IfIt.title == "") return;
  plot.IfIt.dimension = glm::ivec2(-1, height);
  utl_plot->plot_regression(&plot.IfIt);

  //---------------------------
}
void Model::plot_model_heatmap(dat::base::Sensor& sensor, float height){
  dat::sensor::Model* model = rad_model->get_model(sensor, "NFOV");
  rad::cor::structure::Plot& plot = rad_struct->plot;
  //---------------------------

  if(plot.IfRIt.title == "") return;
  plot.IfRIt.dimension = glm::ivec2(-1, height);
  bool need_update = utl_plot->plot_heatmap(&plot.IfRIt, &model->axis_x, &model->axis_y);
  if(need_update){
    rad_plot->update(sensor);
  }

  //---------------------------
}


}
