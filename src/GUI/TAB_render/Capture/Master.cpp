#include "Master.h"

#include <GUI.h>


namespace gui::kinect{

//Constructor / Destructor
Master::Master(k4n::Node* node_kinect){
  //---------------------------

  this->node_kinect = node_kinect;
  this->k4n_swarm = node_kinect->get_k4n_swarm();

  this->item_width = 100;

  //---------------------------
}
Master::~Master(){}

//Main function
void Master::tab_master(k4n::dev::Master* master){
  //---------------------------

  this->show_info(master);
  ImGui::Separator();
  this->show_colorization(master);
  ImGui::Separator();

  //---------------------------
}

//Subfunction
void Master::show_info(k4n::dev::Master* master){
  k4n::dev::Sensor* sensor = k4n_swarm->get_selected_sensor();
  if(sensor == nullptr) return;
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
void Master::show_colorization(k4n::dev::Master* master){
  k4n::dev::Sensor* k4n_sensor = k4n_swarm->get_selected_sensor();
  if(k4n_sensor == nullptr) return;
  //---------------------------

  //Colorization mode
  static int color_mode = 2;
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Colorization");
  ImGui::RadioButton("RGB##colorization", &k4n_sensor->cloud.color_mode, 0);
  ImGui::SameLine();
  ImGui::RadioButton("##unicolor", &k4n_sensor->cloud.color_mode, 1);
  ImGui::SameLine();
  ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar;
  ImGui::ColorEdit4("##unicolor_choice", (float*)&k4n_sensor->object->data->unicolor, flags);
  ImGui::SameLine();
  ImGui::RadioButton("I##colorization", &k4n_sensor->cloud.color_mode, 2);
  ImGui::SameLine();
  ImGui::RadioButton("Heatmap##colorization", &k4n_sensor->cloud.color_mode, 3);

  //Intensity cursor
  if(k4n_sensor->cloud.color_mode == 2){
    ImGui::SetNextItemWidth(100);
    ImGui::SliderInt("Intensity division", &k4n_sensor->cloud.intensity_division, 1, 5000);
  }

  //Heatmap mode
  if(k4n_sensor->cloud.color_mode == 3){
    ImGui::Indent();
    ImGui::RadioButton("I##heatmap", &k4n_sensor->cloud.heatmap_mode, 0);
    ImGui::SameLine();
    ImGui::RadioButton("H##heatmap", &k4n_sensor->cloud.heatmap_mode, 1);
    ImGui::SameLine();
    ImGui::RadioButton("R##heatmap", &k4n_sensor->cloud.heatmap_mode, 2);

    //Intensity heatmap
    if(k4n_sensor->cloud.heatmap_mode == 0){
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("I diviser", &k4n_sensor->cloud.intensity_division, 1, 5000);
    }

    //Height heatmap
    if(k4n_sensor->cloud.heatmap_mode == 1){
      float min = k4n_sensor->object->pose->min.z + 10;
      float max = k4n_sensor->object->pose->min.z + 10;
      ImGui::SetNextItemWidth(125);
      ImGui::DragFloatRange2("Z##321", &k4n_sensor->cloud.range_height.x, &k4n_sensor->cloud.range_height.y, 0.1f, min, max, "%.1f", "%.1f");
    }
    ImGui::Unindent();
  }

  //---------------------------
}

}
