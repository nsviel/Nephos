#include "Panel.h"

#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace ldr::gui::importer{

//Constructor / Destructor
Panel::Panel(ldr::Node* node_loader, bool* show_window) : ldr::gui::Navigator(node_loader){
  //---------------------------

  dat::Node* node_data = node_loader->get_node_data();

  this->dat_graph = node_data->get_dat_graph();
  this->dat_set = node_data->get_dat_set();
  this->ldr_struct = node_loader->get_ldr_struct();
  this->ldr_importer = node_loader->get_ldr_importer();
  this->ldr_bookmark = node_loader->get_ldr_bookmark();

  this->name = "Import##555";
  this->show_window = show_window;
  this->with_bookmark = true;

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
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
void Panel::design_panel(){
  ImGuiTabItemFlags flag = 0;
  //---------------------------

  if(goto_file_tab){
    flag = ImGuiTabItemFlags_SetSelected;
    this->goto_file_tab = false;
  }

  this->draw_header();
  ImGui::Separator();

  ImVec2 size = ImGui::GetContentRegionAvail();
  if(ImGui::BeginTabBar("Panel_tab##4567")){
    //File manager loader
    ImGui::SetNextItemWidth(size.x/2);
    if(ImGui::BeginTabItem("File##50", NULL, flag)){
      this->draw_navigator();
      ImGui::EndTabItem();
    }

    //Bookmark loader
    ImGui::SetNextItemWidth(size.x/2);
    if(ImGui::BeginTabItem("Bookmark##50", NULL)){
      this->draw_bookmark_tab();
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}

//Subfunction
void Panel::draw_header(){
  //---------------------------

  //Load button
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button("Load##222", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
    this->item_operation();
    this->vec_selection.clear();
  }
  ImGui::PopStyleColor(2);

  // Load button + selected path
  ImGui::BeginTable("header##exporter", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);
  ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthStretch);

  //Selected file path
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Path"); ImGui::TableNextColumn();
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", ldr_struct->get_current_path().c_str());
  ImGui::EndTable();

  // Scale new
  ImGui::SetNextItemWidth(75);
  ImGui::DragFloat("Scale##4567", &ldr_struct->import_scaling, 0.1, 0.1, 100, "%.2f x");

  // Remove old
  ImGui::SameLine();
  ImGui::Checkbox("Remove##222", &ldr_struct->import_remove_old);

  // Center new
  ImGui::SameLine();
  ImGui::Checkbox("Centered##222", &ldr_struct->import_center);

  //---------------------------
}
void Panel::draw_bookmark_tab(){
  std::list<ldr::bookmark::Item> list_item = ldr_bookmark->get_list_item();
  //---------------------------

  for(int i=0; i<list_item.size(); i++){
    ldr::bookmark::Item& item = *next(list_item.begin(), i);
    ldr::gui::File file;
    file.item = item;

    //File type icon
    ImVec4 color_icon = ImVec4(file.item.color_icon.r, file.item.color_icon.g, file.item.color_icon.b, file.item.color_icon.a);
    ImGui::TextColored(color_icon, "%s", file.item.icon.c_str());

    //Bookmark name button
    ImGui::SameLine();
    int trash_space = 0;
    file.item.is_supressible ? trash_space = 30 : 0;
    int size = ImGui::GetContentRegionAvail().x - trash_space;
    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.04, 0.5));
    if(ImGui::Button(file.item.name.c_str(), ImVec2(size, 0))){
      this->item_bookmark(file.item.path);
    }
    ImGui::PopStyleVar();
    ImGui::SetItemTooltip("%s", file.item.path.c_str());

    //Bookmark supression
    if(file.item.is_supressible){
      ImGui::SameLine();
      std::string ID = file.item.path + "##supressionbookmark";
      ImGui::PushID(ID.c_str());
      if(ImGui::Button(ICON_FA_TRASH "##supressionbookmark")){
        ldr_bookmark->remove_path(file.item.path);
        ldr_bookmark->save_on_file();
      }
      ImGui::PopID();
    }
  }

  //---------------------------
}

//Operation function
void Panel::item_operation(){
  //---------------------------

  //Retrieve all good selected files to load
  std::vector<std::string> vec_path;
  for(int i=0; i<vec_file.size(); i++){
    ldr::gui::File& file = vec_file[i];
    if(vec_selection.contains(file.item.ID)){
      if(ldr_importer->is_format_supported(file.item.format)){
        vec_path.push_back(file.item.path);
      }
    }
  }
  if(vec_path.size() == 0) return;

  //Run all file loading
  for(int i=0; i<vec_path.size(); i++){
    utl::base::Path path;
    path.data = vec_path[i];
    ldr_importer->load_object(path);
  }

  //---------------------------
}
void Panel::item_bookmark(std::string file_path){
  //---------------------------

  //If selection is a directory go display his content
  if(utl::directory::is_directory(file_path)){
    ldr_struct->current_dir = file_path;
    this->goto_file_tab = true;
  }
  //If selection is a file go load it
  else{
    //File check
    std::string format = utl::path::get_format_from_path(file_path);
    if(!utl::file::is_exist(file_path)) return;
    if(!ldr_importer->is_format_supported(format)) return;

    //File load
    utl::base::Path path;
    path.data = file_path;
    ldr_importer->load_object(path);
  }

  //---------------------------
}

}
