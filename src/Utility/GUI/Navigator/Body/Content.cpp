#include "Content.h"

#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace utl::gui::navigator{

//Constructor / Destructor
Content::Content(utl::gui::Navigator* navigator){
  //---------------------------

  this->nav_struct = navigator->get_nav_struct();
  this->nav_selection = navigator->get_nav_selection();
  this->nav_organisation = new utl::gui::navigator::Organisation(navigator);

  //---------------------------
}
Content::~Content(){}

//Main function
void Content::draw_content(utl::base::Path& path){
  //---------------------------

  //Content table
  static ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_BordersV;
  flags |= ImGuiTableFlags_BordersOuterH;
  flags |= ImGuiTableFlags_Resizable;
  flags |= ImGuiTableFlags_RowBg;
  flags |= ImGuiTableFlags_NoBordersInBody;
  flags |= ImGuiTableFlags_Sortable;

  int nb_column = 3 + nav_struct->vec_icon.size();

  ImGui::BeginTable("init_tree", nb_column, flags);
  ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_DefaultSort, 175, utl::gui::navigator::NAME);
  ImGui::TableSetupColumn("Format", ImGuiTableColumnFlags_WidthFixed, 75, utl::gui::navigator::FORMAT);
  ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, 75, utl::gui::navigator::WEIGHT);
  for(int i=0; i<nav_struct->vec_icon.size(); i++){
    std::string label = "##icon_" + std::to_string(i);
    ImGui::TableSetupColumn(label.c_str(), ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 20);
  }
  ImGui::TableHeadersRow();

  //Content draw
  nav_organisation->update_item_list(path);
  for(int i=0; i<nav_struct->vec_item.size(); i++){
    utl::gui::navigator::Item& item = nav_struct->vec_item[i];

    this->draw_item(item);
    this->draw_icon(item);
    nav_selection->selection_item(path, item);
  }

  ImGui::EndTable();

  //---------------------------
}

//Subfunction
void Content::draw_item(utl::gui::navigator::Item& item){
  //---------------------------

  ImVec4 color_icon = ImVec4(item.color_icon.r, item.color_icon.g, item.color_icon.b, item.color_icon.a);
  ImVec4 color_text = ImVec4(item.color_text.r, item.color_text.g, item.color_text.b, item.color_text.a);

  ImGui::TableNextRow();

  //Item icon + name
  ImGui::TableNextColumn();
  ImGui::TextColored(color_icon, "%s", item.icon.c_str());
  ImGui::SameLine();
  ImGui::TextColored(color_text, "%s", item.name.c_str());

  //Item format
  ImGui::TableNextColumn();
  ImGui::TextColored(color_text, "%s", item.format.c_str());

  //Item size
  ImGui::TableNextColumn();
  ImGui::TextColored(color_text, "%s", item.size.c_str());

  //---------------------------
}
void Content::draw_icon(utl::gui::navigator::Item& item){
  //---------------------------

  for(int i=0; i<nav_struct->vec_icon.size(); i++){
    ImGui::TableNextColumn();
    nav_struct->vec_icon[i](item.path);
  }

  //---------------------------
}

}
