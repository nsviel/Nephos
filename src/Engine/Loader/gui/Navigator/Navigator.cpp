#include "Navigator.h"

#include <Loader/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace ldr::gui{

//Constructor / Destructor
Navigator::Navigator(ldr::Node* node_loader, bool with_bookmark){
  //---------------------------

  this->ldr_bookmark = node_loader->get_ldr_bookmark();
  this->nav_struct = new ldr::gui::navigator::Structure();
  this->nav_organisation = new ldr::gui::navigator::Organisation(nav_struct);
  this->nav_header = new ldr::gui::navigator::Header(nav_struct);
  this->nav_selection = new ldr::gui::navigator::Selection(nav_struct);

  nav_struct->with_bookmark = with_bookmark;
  nav_struct->default_path = utl::path::get_current_parent_path_abs();

  //---------------------------
}
Navigator::~Navigator(){}

//Main function
void Navigator::draw_navigator(utl::base::Path& path){
  //---------------------------

  nav_header->draw_header(path);
  nav_organisation->recolt_items(path);
  this->draw_content(path);

  //---------------------------
}

//Subfunction
void Navigator::draw_content(utl::base::Path& path){
  //---------------------------

  //Content table
  static ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_BordersV;
  flags |= ImGuiTableFlags_BordersOuterH;
  flags |= ImGuiTableFlags_Resizable;
  flags |= ImGuiTableFlags_RowBg;
  flags |= ImGuiTableFlags_NoBordersInBody;
  flags |= ImGuiTableFlags_Sortable;
  ImGui::BeginTable("init_tree", 4, flags);
  ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_DefaultSort, 175, ldr::bookmark::NAME);
  ImGui::TableSetupColumn("Format", ImGuiTableColumnFlags_WidthFixed, 75, ldr::bookmark::FORMAT);
  ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, 75, ldr::bookmark::WEIGHT);
  ImGui::TableSetupColumn("##bookmark_1", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 20);
  ImGui::TableHeadersRow();

  //Content draw
  nav_organisation->sort_items();
  this->draw_item_content(path);

  ImGui::EndTable();

  //---------------------------
}
void Navigator::draw_item_content(utl::base::Path& path){
  //---------------------------

  // Populate the table
  for(int i=0; i<nav_struct->vec_item.size(); i++){
    ldr::gui::navigator::File& file = nav_struct->vec_item[i];

    this->draw_content_file(file);
    this->draw_bookmark_icon(file);
    nav_selection->selection_item(file);
  }

  //---------------------------
}
void Navigator::draw_content_file(ldr::gui::navigator::File& file){
  //---------------------------

  ImVec4 color_icon = ImVec4(file.item.color_icon.r, file.item.color_icon.g, file.item.color_icon.b, file.item.color_icon.a);
  ImVec4 color_text = ImVec4(file.item.color_text.r, file.item.color_text.g, file.item.color_text.b, file.item.color_text.a);

  ImGui::TableNextRow();

  //Item icon + name
  ImGui::TableNextColumn();
  ImGui::TextColored(color_icon, "%s", file.item.icon.c_str());
  ImGui::SameLine();
  ImGui::TextColored(color_text, "%s", file.item.name.c_str());

  //Item format
  ImGui::TableNextColumn();
  ImGui::TextColored(color_text, "%s", file.item.format.c_str());

  //Item size
  ImGui::TableNextColumn();
  ImGui::TextColored(color_text, "%s", file.item.size.c_str());

  //---------------------------
}
void Navigator::draw_bookmark_icon(ldr::gui::navigator::File& file){
  if(nav_struct->with_bookmark == false) return;
  //---------------------------

  //Button background if already bookmarked
  bool is_bookmarked = ldr_bookmark->is_path_bookmarked(file.item.path);
  int bg_alpha;
  is_bookmarked ? bg_alpha = 255 : bg_alpha = 0;

  //Draw bookmark button
  std::string ID = file.item.path + "##bookmarkbutton";
  ImGui::TableNextColumn();
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

}
