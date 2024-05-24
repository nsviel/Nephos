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
      this->show_transformation_mode(master);
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
void Master::show_transformation_mode(k4n::dev::Master* master){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Transformation");

  ImGui::RadioButton("Depth to color", &master->config.depth.transformation_mode, k4n::depth::DEPTH_TO_COLOR);
  ImGui::SameLine();
  ImGui::RadioButton("Color to depth", &master->config.depth.transformation_mode, k4n::depth::COLOR_TO_DEPTH);

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
  if(ImGui::RadioButton("MKV", &master->recorder.mode, dyn::recorder::MKV)){
    master->recorder.folder = "../media/record/mkv";
  }
  ImGui::SameLine();
  if(ImGui::RadioButton("PLY", &master->recorder.mode, dyn::recorder::PLY)){
    master->recorder.folder = "../media/record/ply";
  }

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
