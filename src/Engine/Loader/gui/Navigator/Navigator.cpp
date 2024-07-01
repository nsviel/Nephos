#include "Navigator.h"

#include <Loader/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace ldr::gui{

//Constructor / Destructor
Navigator::Navigator(ldr::Node* node_loader, bool with_bookmark){
  //---------------------------

  this->nav_struct = new ldr::gui::navigator::Structure();
  this->ldr_importer = node_loader->get_ldr_importer();
  this->ldr_bookmark = node_loader->get_ldr_bookmark();
  this->nav_organisation = new ldr::gui::navigator::Organisation(nav_struct);
  this->nav_header = new ldr::gui::navigator::Header(nav_struct);

  nav_struct->with_bookmark = with_bookmark;
  nav_struct->default_path = utl::path::get_current_parent_path_abs();

  //---------------------------
}
Navigator::~Navigator(){}

//Main function
void Navigator::draw_navigator(utl::base::Path& path){

  //---------------------------

  nav_header->draw_header(path);
  nav_organisation->organize_items(path);
  this->draw_file_content(path);

  //---------------------------
}

//Subfunction
void Navigator::draw_file_content(utl::base::Path& path){
  //---------------------------

  static ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_BordersV;
  flags |= ImGuiTableFlags_BordersOuterH;
  flags |= ImGuiTableFlags_Resizable;
  flags |= ImGuiTableFlags_RowBg;
  flags |= ImGuiTableFlags_NoBordersInBody;
  flags |= ImGuiTableFlags_Sortable;
  ImGui::BeginTable("init_tree", 4, flags);
  // The first column will use the default _WidthStretch when ScrollX is Off and _WidthFixed when ScrollX is On
  ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_DefaultSort, 175, ldr::bookmark::NAME);
  ImGui::TableSetupColumn("Format", ImGuiTableColumnFlags_WidthFixed, 75, ldr::bookmark::FORMAT);
  ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, 75, ldr::bookmark::WEIGHT);
  ImGui::TableSetupColumn("##bookmark_1", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 20);
  ImGui::TableHeadersRow();

  this->item_folder(path);
  this->item_file(path);

  ImGui::EndTable();

  //---------------------------
}
void Navigator::item_folder(utl::base::Path& path){
  //---------------------------

  // Populate the table - Folder
  ImGuiSelectableFlags flags;
  flags |= ImGuiSelectableFlags_SpanAllColumns;
  flags |= ImGuiSelectableFlags_AllowOverlap;
  flags |= ImGuiSelectableFlags_AllowDoubleClick;
  for(int i=0; i<nav_struct->vec_folder.size(); i++){
    ldr::gui::navigator::File& file = nav_struct->vec_folder[i];

    ImGui::TableNextColumn();
    ImVec4 color_icon = ImVec4(file.item.color_icon.r, file.item.color_icon.g, file.item.color_icon.b, file.item.color_icon.a);
    ImGui::TextColored(color_icon, "%s", file.item.icon.c_str());
    ImGui::SameLine();
    ImVec4 color_text = ImVec4(file.item.color_text.r, file.item.color_text.g, file.item.color_text.b, file.item.color_text.a);
    ImGui::TextColored(color_text, "%s", file.item.name.c_str());
    ImGui::TableNextColumn();
    ImGui::TextColored(color_text, "%s", file.item.format.c_str());
    ImGui::TableNextColumn();
    ImGui::TextColored(color_text, "%s", file.item.size.c_str());
    ImGui::TableNextColumn();
    this->draw_bookmark_icon(file);

    //Selection stuff
    ImGui::SameLine();
    bool item_is_selected = nav_struct->vec_selection.contains(file.item.ID);
    std::string name = "##" + std::to_string(file.item.ID);
    if(ImGui::Selectable(name.c_str(), item_is_selected, flags)){
      this->make_selection(file, item_is_selected);

      if(ImGui::IsMouseDoubleClicked(0)){
        if(file.item.name == ".."){
          std::filesystem::path fs_path = path.directory;
          path.directory = fs_path.parent_path();
          nav_struct->vec_selection.clear();
        }else{
          path.directory += "/" + file.item.name;
          nav_struct->vec_selection.clear();
        }
      }

    }
  }

  //---------------------------
}
void Navigator::item_file(utl::base::Path& path){
  //---------------------------

  // Populate the table - File
  ImGuiSelectableFlags flags;
  flags |= ImGuiSelectableFlags_SpanAllColumns;
  flags |= ImGuiSelectableFlags_AllowOverlap;
  flags |= ImGuiSelectableFlags_AllowDoubleClick;
  for(int i=0; i<nav_struct->vec_file.size(); i++){
    ldr::gui::navigator::File& file = nav_struct->vec_file[i];

    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImVec4 color_icon = ImVec4(file.item.color_icon.r, file.item.color_icon.g, file.item.color_icon.b, file.item.color_icon.a);
    ImGui::TextColored(color_icon, "%s", file.item.icon.c_str());
    ImGui::SameLine();
    ImVec4 color_text = ImVec4(file.item.color_text.r, file.item.color_text.g, file.item.color_text.b, file.item.color_text.a);
    ImGui::TextColored(color_text, "%s", file.item.name.c_str());
    ImGui::TableNextColumn();
    ImGui::TextColored(color_text, "%s", file.item.format.c_str());
    ImGui::TableNextColumn();
    ImGui::TextColored(color_text, "%s", file.item.size.c_str());
    ImGui::TableNextColumn();
    this->draw_bookmark_icon(file);

    //Selection stuff
    ImGui::SameLine();
    bool item_is_selected = nav_struct->vec_selection.contains(file.item.ID);
    std::string name = "##" + std::to_string(file.item.ID);
    if(ImGui::Selectable(name.c_str(), item_is_selected, flags)){
      this->make_selection(file, item_is_selected);

      //If double clicked, load it
      if(ImGui::IsMouseDoubleClicked(0)){
        nav_struct->vec_selection.clear();
        nav_struct->vec_selection.push_back(file.item.ID);
        this->item_operation();
      }
    }
  }

  //---------------------------
}

//Item function
void Navigator::draw_bookmark_icon(ldr::gui::navigator::File& file){
  if(nav_struct->with_bookmark == false) return;
  //---------------------------

  //Button background if already bookmarked
  bool is_bookmarked = ldr_bookmark->is_path_bookmarked(file.item.path);
  int bg_alpha;
  is_bookmarked ? bg_alpha = 255 : bg_alpha = 0;

  //Draw bookmark button
  std::string ID = file.item.path + "##bookmarkbutton";
  ImGui::PushID(ID.c_str());
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, bg_alpha));
  ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(46, 133, 45, 0));
  if(ImGui::Button(ICON_FA_BOOKMARK "##addbookmark")){
    if(is_bookmarked){
      ldr_bookmark->remove_path(file.item.path);
    }else{
      ldr_bookmark->add_abs_path(file.item.path);
    }
    ldr_bookmark->save_on_file();
  }
  ImGui::PopStyleColor(2);
  ImGui::PopID();

  //---------------------------
}
void Navigator::make_selection(ldr::gui::navigator::File& file, bool& already_selected){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  if(io.KeyCtrl){
    if(already_selected){
      nav_struct->vec_selection.find_erase_unsorted(file.item.ID);
    }
    else{
      nav_struct->vec_selection.push_back(file.item.ID);
    }
  }else{
    nav_struct->vec_selection.clear();
    nav_struct->vec_selection.push_back(file.item.ID);
  }

  //---------------------------
}
void Navigator::item_selection(utl::base::Path& path){
  //---------------------------

  int selection = nav_struct->vec_selection[nav_struct->vec_selection.size() - 1];
  for(int i=0; i<nav_struct->vec_file.size(); i++){
    ldr::gui::navigator::File& file = nav_struct->vec_file[i];

    if(file.item.ID == selection){
      path.directory = utl::path::get_dir_from_path(file.item.path);
      path.name = utl::path::get_name_from_path(file.item.path);
      path.format = utl::path::get_format_from_path(file.item.path);
    }
  }

  //---------------------------
}

}
