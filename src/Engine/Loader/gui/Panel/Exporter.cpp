#include "Exporter.h"

#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace ldr::gui{

//Constructor / Destructor
Exporter::Exporter(ldr::Node* node_loader, bool* show_window) : ldr::gui::Navigator(node_loader, false){
  //---------------------------

  this->default_dir = utl::path::get_current_parent_path_abs();
  this->current_dir = default_dir;
  this->current_path = "(not defined)";
  this->name = "Exporter";
  this->show_window = show_window;

  //---------------------------
}
Exporter::~Exporter(){}

//Main function
void Exporter::run_panel(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(400, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Exporter::design_panel(){
  //---------------------------

  this->draw_header();
  this->draw_navigator();

  //---------------------------
}

//Subfunction
void Exporter::draw_header(){
  //---------------------------

  ImGui::BeginTable("header##exporter", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 75.0f);
  ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthStretch);

  //filename
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Path");
  ImGui::TableNextColumn();
  static char str_n[256];
  strncpy(str_n, current_path.c_str(), sizeof(str_n) - 1);
  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
  if(ImGui::InputText("##exporter", str_n, IM_ARRAYSIZE(str_n))){
    this->current_path = str_n;
  }

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Exporter::item_selection(){
  //---------------------------
/*
  //Retrieve all good selected files to load
  std::vector<std::string> vec_path;
  for(int i=0; i<vec_bookmark_file.size(); i++){
    ldr::gui::File& bookmark = vec_bookmark_file[i];
    if(vec_selection.contains(bookmark.item.ID)){
      if(ldr_importer->is_format_supported(bookmark.item.format)){
        vec_path.push_back(bookmark.item.path);
      }
    }
  }
  if(vec_path.size() == 0) return;

  //Apply loading and operations
  if(param_remove_old){
    dat::base::Set* set_graph = dat_graph->get_set_graph();
    dat_set->remove_all_entity(set_graph);
  }

  for(int i=0; i<vec_path.size(); i++){
    utl::media::Path path;
    path.data = vec_path[i];

    dat::base::Object* object = ldr_importer->load_object(path);

    if(object != nullptr){
      this->operation_entity(object);
    }
  }
*/
  //---------------------------
}

}
