#include "Master.h"

#include <K4N/Namespace.h>


namespace eng::k4n::gui{

//Constructor / Destructor
Master::Master(eng::k4n::Node* node_k4n){
  //---------------------------

  this->node_k4n = node_k4n;
  this->k4n_swarm = node_k4n->get_k4n_swarm();

  this->item_width = 100;

  //---------------------------
}
Master::~Master(){}

//Main function
void Master::show_master_info(eng::k4n::dev::Master* master){
  //---------------------------

  this->show_info(master);
  ImGui::Separator();
  this->show_colorization(master);
  ImGui::Separator();
  this->show_voxelizer(master);
  ImGui::Separator();

  //---------------------------
}

//Subfunction
void Master::show_info(eng::k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------

    ImGui::Separator();
  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  if(ImGui::BeginTable("Kinect_info##general", 2)){
    //Type
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Type"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", master->type.c_str());

    //Duration
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Duration"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.2f s", master->player.duration);

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
void Master::show_colorization(eng::k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Colorization");

  //Colorization mode
  static int color_mode = 2;
  ImGui::RadioButton("RGB##colorization", &master->operation.color_mode, 0);
  ImGui::SameLine();
  ImGui::RadioButton("##unicolor", &master->operation.color_mode, 1);
  ImGui::SameLine();
  ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar;
  ImGui::ColorEdit4("##unicolor_choice", (float*)&master->operation.unicolor, flags);
  ImGui::SameLine();
  ImGui::RadioButton("I##colorization", &master->operation.color_mode, 2);
  ImGui::SameLine();
  ImGui::RadioButton("Heatmap##colorization", &master->operation.color_mode, 3);

  //Intensity cursor
  if(master->operation.color_mode == 2){
    ImGui::SetNextItemWidth(100);
    ImGui::SliderInt("Intensity division", &master->operation.intensity_division, 1, 5000);
  }

  //Heatmap mode
  if(master->operation.color_mode == 3){
    ImGui::Indent();
    ImGui::RadioButton("I##heatmap", &master->operation.heatmap_mode, 0);
    ImGui::SameLine();
    ImGui::RadioButton("H##heatmap", &master->operation.heatmap_mode, 1);
    ImGui::SameLine();
    ImGui::RadioButton("R##heatmap", &master->operation.heatmap_mode, 2);

    //Intensity heatmap
    if(master->operation.heatmap_mode == 0){
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("I diviser", &master->operation.intensity_division, 1, 5000);
    }

    //Height heatmap
    if(master->operation.heatmap_mode == 1){
      float min = master->pose.min.z + 10;
      float max = master->pose.max.z + 10;
      ImGui::SetNextItemWidth(125);
      ImGui::DragFloatRange2("Z##321", &master->operation.range_height.x, &master->operation.range_height.y, 0.1f, min, max, "%.1f", "%.1f");
    }
    ImGui::Unindent();
  }

  //---------------------------
}
void Master::show_voxelizer(eng::k4n::dev::Master* master){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Voxel");

  //Voxel size
  ImGui::SetNextItemWidth(100);
  ImGui::SliderFloat("Size", &master->voxel.voxel_size, 0.1, 5, "%.2f");

  //Voxel minimal number of points
  ImGui::SetNextItemWidth(100);
  ImGui::SliderInt("Minimum point", &master->voxel.min_nb_point, 1, 1000);

  //---------------------------
}

}
