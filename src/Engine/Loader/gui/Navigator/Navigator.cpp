#include "Navigator.h"

#include <Loader/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace ldr::gui{

//Constructor / Destructor
Navigator::Navigator(){
  //---------------------------

  this->nav_struct = new ldr::gui::navigator::Structure();
  this->nav_organisation = new ldr::gui::navigator::Organisation(nav_struct);
  this->nav_header = new ldr::gui::navigator::Header(nav_struct);
  this->nav_selection = new ldr::gui::navigator::Selection(nav_struct);

  nav_struct->default_path = utl::path::get_current_directory_path();

  //---------------------------
}
Navigator::~Navigator(){}

//Main function
void Navigator::draw_navigator(utl::base::Path& path){
  //---------------------------

  nav_header->draw_header(path);
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
  nav_organisation->update_item_list(path);
  for(int i=0; i<nav_struct->vec_item.size(); i++){
    ldr::gui::navigator::File& file = nav_struct->vec_item[i];

    this->draw_item(file);
    nav_selection->selection_item(path, file);
  }

  ImGui::EndTable();

  //---------------------------
}
void Navigator::draw_item(ldr::gui::navigator::File& file){
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


}
