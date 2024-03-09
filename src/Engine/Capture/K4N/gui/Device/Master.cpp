#include "Master.h"

#include <K4N/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Master::Master(k4n::Node* node_k4n){
  //---------------------------

  this->node_k4n = node_k4n;
  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->gui_capture = new k4n::gui::Capture(node_k4n);
  this->gui_playback = new k4n::gui::Playback(node_k4n);

  this->item_width = 100;

  //---------------------------
}
Master::~Master(){}

//Main function
void Master::show_master_info(k4n::dev::Master* master){
  //---------------------------

  this->show_info(master);
  gui_capture->list_device(master);

  if(ImGui::BeginTabBar("master_option##tab")){
    this->show_operation(master);

    //Capture or playback
    if(master->mode == k4n::dev::PLAYBACK){
      gui_playback->show_master_playback(master);
    }else{
      gui_capture->show_master_capture(master);
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}

//Subfunction
void Master::show_info(k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------

  //Master general info
  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  if(ImGui::BeginTable("master##info", 2)){
    //Type
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Type"); ImGui::TableNextColumn();
    string mode = master->mode == k4n::dev::CAPTURE ? "capture" : "playback";
    string type = master->type + "::" + mode;
    ImGui::TextColored(color, "%s", type.c_str());

    //Recording time
    if(master->player.record){
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Record"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%.2f s", master->recorder.ts_rec);
    }

    ImGui::EndTable();
  }

  //---------------------------
}
void Master::show_operation(k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------

  if(ImGui::BeginTabItem("Operation##3443", NULL)){
    this->show_transformation(master);
    this->show_colorization(master);
    this->show_voxelization(master);
    this->show_normal(master);
    ImGui::EndTabItem();
  }

  //---------------------------
}

//Processing function
void Master::show_transformation(k4n::dev::Master* master){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Transformation");

  int transformation_mode = 0;
  ImGui::RadioButton("Depth to color", &master->operation.transformation_mode, k4n::transformation::DEPTH_TO_COLOR);
  ImGui::SameLine();
  ImGui::RadioButton("Color to depth", &master->operation.transformation_mode, k4n::transformation::COLOR_TO_DEPTH);

  //---------------------------
  ImGui::Separator();
}
void Master::show_colorization(k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Colorization");

  //Colorization mode
  ImGui::RadioButton("RGB##colorization", &master->operation.color_mode, ope::color::CAMERA);
  ImGui::SameLine();
  ImGui::RadioButton("##unicolor", &master->operation.color_mode, ope::color::UNICOLOR);
  ImGui::SameLine();
  ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar;
  ImGui::ColorEdit4("##unicolor_choice", (float*)&master->operation.unicolor, flags);
  ImGui::SameLine();
  ImGui::RadioButton("I##colorization", &master->operation.color_mode, ope::color::INTENSITY);
  ImGui::SameLine();
  ImGui::RadioButton("Heatmap##colorization", &master->operation.color_mode, ope::color::HEATMAP);
  ImGui::SameLine();
  ImGui::RadioButton("Structure##colorization", &master->operation.color_mode, ope::color::STRUCTURE);

  //Intensity cursor
  if(master->operation.color_mode == ope::color::INTENSITY){
    ImGui::SetNextItemWidth(100);
    ImGui::SliderInt("Intensity division", &master->operation.intensity_division, 1, 5000);
  }

  //Heatmap mode
  if(master->operation.color_mode == ope::color::HEATMAP){
    ImGui::Indent();
    ImGui::RadioButton("I##heatmap", &master->operation.heatmap_mode, ope::color::heatmap::INTENSITY);
    ImGui::SameLine();
    ImGui::RadioButton("H##heatmap", &master->operation.heatmap_mode, ope::color::heatmap::HEIGHT);
    ImGui::SameLine();
    ImGui::RadioButton("R##heatmap", &master->operation.heatmap_mode, ope::color::heatmap::RANGE);

    //Intensity heatmap
    if(master->operation.heatmap_mode == ope::color::heatmap::INTENSITY){
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("I diviser", &master->operation.intensity_division, 1, 5000);
    }

    //Height heatmap
    if(master->operation.heatmap_mode == ope::color::heatmap::HEIGHT){
      float min = master->pose.min.z + 10;
      float max = master->pose.max.z + 10;
      ImGui::SetNextItemWidth(125);
      ImGui::DragFloatRange2("Z##321", &master->operation.range_height.x, &master->operation.range_height.y, 0.1f, min, max, "%.1f", "%.1f");
    }
    ImGui::Unindent();
  }

  //---------------------------
  ImGui::Separator();
}
void Master::show_voxelization(k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------

  if(!master->operation.voxelization) return;
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Voxel");

  //Voxel size
  ImGui::SetNextItemWidth(100);
  ImGui::SliderFloat("Size", &master->operation.voxel_size, 0.1, 5, "%.2f");

  //Voxel minimal number of points
  ImGui::SetNextItemWidth(100);
  ImGui::SliderInt("Minimum point", &master->operation.voxel_min_point, 1, 1000);

  //---------------------------
  ImGui::Separator();
}
void Master::show_normal(k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Normal");

  if(ImGui::Checkbox("Visible##2242", &master->operation.normal_visible)){
    master->visibility_normal();
  }
  ImGui::SameLine();

  ImGui::SetNextItemWidth(100);
  ImGui::SliderInt("kNN", &master->operation.normal_knn, 1, 10);

  //---------------------------
  ImGui::Separator();
}

}
