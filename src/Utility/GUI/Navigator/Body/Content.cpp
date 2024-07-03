#include "Content.h"

#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace utl::gui::navigator{

//Constructor / Destructor
Content::Content(utl::gui::navigator::Structure* nav_struct){
  //---------------------------

  this->nav_struct = nav_struct;
  this->nav_organisation = new utl::gui::navigator::Organisation(nav_struct);
  this->nav_selection = new utl::gui::navigator::Selection(nav_struct);

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
  //ImGui::TableSetupColumn("##bookmark_1", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 20);
  ImGui::TableHeadersRow();

  //Content draw
  nav_organisation->update_item_list(path);
  for(int i=0; i<nav_struct->vec_item.size(); i++){
    utl::gui::navigator::File& file = nav_struct->vec_item[i];

    this->draw_item(file);
    this->draw_icon(file);
    nav_selection->selection_item(path, file);
  }

  ImGui::EndTable();

  //---------------------------
}

//Subfunction
void Content::draw_item(utl::gui::navigator::File& file){
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
void Content::draw_icon(utl::gui::navigator::File& file){
  //---------------------------

  for(int i=0; i<nav_struct->vec_icon.size(); i++){
    ImGui::TableNextColumn();
    nav_struct->vec_icon[i]();
  }

  //---------------------------
}

}
