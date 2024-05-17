#include "Master.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Master::Master(k4n::Node* node_k4n){
  //---------------------------

  this->node_k4n = node_k4n;
  this->gui_capture = new k4n::gui::Capture(node_k4n);
  this->gui_playback = new k4n::gui::Playback(node_k4n);

  this->item_width = 100;

  //---------------------------
}
Master::~Master(){}

//Main function
void Master::show_info(k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------

  //Master general info
  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  if(ImGui::BeginTable("master##info", 2)){
    //Type
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Type"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", master->type.c_str());

    //Recording time
    if(master->player->record){
      //Recording time
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Record"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%.2f s", master->recorder.ts_rec);

      //Recording file size
      if(master->recorder.mode == dyn::recorder::MKV){
        ImGui::TableNextRow(); ImGui::TableNextColumn();
        ImGui::Text("Size"); ImGui::TableNextColumn();
        ImGui::TextColored(color, "%.2f Mo", master->recorder.file_size);
      }
    }

    ImGui::EndTable();
  }

  gui_playback->show_info_playback(master);
  gui_capture->show_list_device(master);

  //---------------------------
}
void Master::show_parameter(k4n::dev::Master* master){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(39, 74, 90, 255));
  ImGui::PushStyleColor(ImGuiCol_TabHovered, IM_COL32(54, 112, 131, 255));
  ImGui::PushStyleColor(ImGuiCol_TabActive, IM_COL32(44, 101, 131, 255));
  if(ImGui::BeginTabBar("master_option##tab")){
    ImGui::SetNextItemWidth(75);
    if(ImGui::BeginTabItem("Operation##tab_item", NULL)){
      this->show_transformation(master);
      this->show_colorization(master);
      this->show_possible_ope(master);
      this->show_voxelization(master);
      this->show_normal(master);
      this->show_recorder(master);
      ImGui::EndTabItem();
    }

    gui_capture->show_info_master(master);

    ImGui::EndTabBar();
  }
  ImGui::PopStyleColor(3);

  //---------------------------
}

//Subfunction
void Master::show_transformation(k4n::dev::Master* master){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Transformation");

  ImGui::RadioButton("Depth to color", &master->config.depth.transformation_mode, k4n::depth::DEPTH_TO_COLOR);
  ImGui::SameLine();
  ImGui::RadioButton("Color to depth", &master->config.depth.transformation_mode, k4n::depth::COLOR_TO_DEPTH);

  //---------------------------
  ImGui::Separator();
}
void Master::show_colorization(k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------
/*
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
    ImGui::SliderInt("Intensity division", &master->operation.intensity_diviser, 1, 5000);
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
      ImGui::SliderInt("I diviser", &master->operation.intensity_diviser, 1, 5000);
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
*/
  //---------------------------
  ImGui::Separator();
}
void Master::show_possible_ope(k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Operation");
  ImGui::Checkbox("Normal##34", &master->operation.normal);
  ImGui::SameLine();
  ImGui::Checkbox("Voxel##33", &master->operation.voxel);
  ImGui::SameLine();
  ImGui::Checkbox("Record##35", &master->recorder.enable);

  //---------------------------
  ImGui::Separator();
}
void Master::show_voxelization(k4n::dev::Master* master){
  if(master == nullptr) return;
  if(!master->operation.voxel) return;
  //---------------------------

  //Activated
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Voxel");

  //Parameter: Voxel size
  ImGui::SetNextItemWidth(100);
  ImGui::SliderFloat("Size", &master->operation.voxel_size, 0.1, 5, "%.2f");

  //Parameter: Voxel minimal number of points
  ImGui::SetNextItemWidth(100);
  ImGui::SliderInt("Minimum point", &master->operation.voxel_min_point, 1, 1000);

  //---------------------------
  ImGui::Separator();
}
void Master::show_normal(k4n::dev::Master* master){
  if(master == nullptr) return;
  if(!master->operation.normal) return;
  //---------------------------

  //Activated
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Normal");

  //Visibility
  if(ImGui::Checkbox("Visible##2242", &master->operation.normal_visible)){
    //master->visibility_normal();
  }

  //Parameter: kNN
  ImGui::SameLine();
  ImGui::SetNextItemWidth(100);
  ImGui::SliderInt("kNN", &master->operation.normal_knn, 1, 10);

  //---------------------------
  ImGui::Separator();
}
void Master::show_recorder(k4n::dev::Master* master){
  if(master == nullptr) return;
  if(!master->recorder.enable) return;
  //---------------------------

  //Intro
  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Record");

  //Mode
  /*bool condition = (master->mode == k4n::dev::PLAYBACK);
  if(condition) ImGui::BeginDisabled();
  if(ImGui::RadioButton("MKV", &master->recorder.mode, dyn::recorder::MKV)){
    master->recorder.folder = "../media/record/mkv";
  }
  if(condition) ImGui::EndDisabled();
  ImGui::SameLine();
  if(ImGui::RadioButton("PLY", &master->recorder.mode, dyn::recorder::PLY)){
    master->recorder.folder = "../media/record/ply";
  }*/

  ImGui::BeginTable("recorder##parameters", 3);

  //filename
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Filename");
  ImGui::TableNextColumn();
  ImGui::TableNextColumn();
  static char str_n[256];
  strcpy(str_n, master->recorder.filename.c_str());
  ImGui::SetNextItemWidth(125);
  if(ImGui::InputText("##filename", str_n, IM_ARRAYSIZE(str_n))){
    master->recorder.filename = str_n;
  }

  //Directory path
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Dir path");
  ImGui::TableNextColumn();
  if(ImGui::Button("...##folder_path", ImVec2(20, 0))){
    zenity::selection_directory(master->recorder.folder);
  }
  ImGui::TableNextColumn();
  if(ImGui::Button(ICON_FA_FOLDER "##folder_path")){
    utl::directory::open(master->recorder.folder);
  }
  ImGui::SameLine();
  string path = (master->recorder.folder != "") ? master->recorder.folder : "(not defined)";
  ImGui::TextColored(color, "%s", path.c_str());

  //Directory file count
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Count");
  ImGui::TableNextColumn();
  if(ImGui::Button("R##folder_file", ImVec2(20, 0))){
    utl::directory::remove(master->recorder.folder);
  }
  ImGui::TableNextColumn();
  int nb_file = utl::directory::size(master->recorder.folder);
  ImGui::TextColored(color, "%d", nb_file);

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}

}
